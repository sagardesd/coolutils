#pragma once

#include <chrono>

namespace cool {

/**
 * @brief A simple stopwatch utility for measuring elapsed time.
 *
 * This class uses `std::chrono::steady_clock` to record time points and compute
 * elapsed durations in milliseconds or seconds. It can be restarted to measure
 * multiple intervals.
 */
struct stopwatch final {
    /**
     * @brief Constructs and starts the stopwatch.
     *
     * Initializes the internal start time to the current steady clock time.
     */
    stopwatch() noexcept;

    /// @brief Default move constructor.
    stopwatch(stopwatch&&) = default;

    /// @brief Default move assignment operator.
    auto operator=(stopwatch&&) -> stopwatch& = default;

    /**
     * @brief Restarts the stopwatch.
     *
     * Resets the internal start time to the current time, effectively starting
     * a new timing interval.
     */
    void restart() noexcept;

    /**
     * @brief Returns the elapsed time in milliseconds since the stopwatch was started or last restarted.
     *
     * @return Elapsed time in milliseconds.
     */
    int64_t elapsed_ms() const noexcept;

    /**
     * @brief Returns the elapsed time in seconds since the stopwatch was started or last restarted.
     *
     * This is equivalent to `elapsed_ms() / 1000`.
     *
     * @return Elapsed time in seconds.
     */
    int64_t elapsed_s() const noexcept;

    /**
     * @brief Returns the start time of the stopwatch in milliseconds since epoch.
     *
     * The epoch is that of `std::chrono::steady_clock`, which may not correspond
     * to wall-clock time but is suitable for measuring durations.
     *
     * @return Start time in milliseconds since the steady clock epoch.
     */
    int64_t starttime_ms() const noexcept;

    /**
     * @brief Returns the start time of the stopwatch in seconds since epoch.
     *
     * This is equivalent to `starttime_ms() / 1000`.
     *
     * @return Start time in seconds since the steady clock epoch.
     */
    int64_t starttime_s() const noexcept;

private:
    /// Internal time point marking when the stopwatch was started or restarted.
    std::chrono::time_point<std::chrono::steady_clock> m_start;
};

/**
 * @brief Measures the duration (in seconds) of executing a callback function.
 *
 * The stopwatch starts before invoking the callback and stops immediately after.
 *
 * @tparam T Callable type.
 * @param callback The function or lambda to measure.
 * @return The number of seconds taken to execute the callback.
 */
template<class T>
int64_t duration_s(T&& callback);

/**
 * @brief Measures the duration (in milliseconds) of executing a callback function.
 *
 * The stopwatch starts before invoking the callback and stops immediately after.
 *
 * @tparam T Callable type.
 * @param callback The function or lambda to measure.
 * @return The number of milliseconds taken to execute the callback.
 */
template<class T>
int64_t duration_ms(T&& callback);

// -----------------------------------------------------------------------------
// Inline Implementations
// -----------------------------------------------------------------------------

inline int64_t stopwatch::starttime_s() const noexcept {
    return starttime_ms() / 1000;
}

inline int64_t stopwatch::elapsed_s() const noexcept {
    return elapsed_ms() / 1000;
}

inline stopwatch::stopwatch() noexcept
    : m_start(std::chrono::steady_clock::now()) {
}

inline void stopwatch::restart() noexcept {
    m_start = std::chrono::steady_clock::now();
}

inline int64_t stopwatch::starttime_ms() const noexcept {
    auto ms = std::chrono::time_point_cast<std::chrono::milliseconds>(m_start);
    return ms.time_since_epoch().count();
}

inline int64_t stopwatch::elapsed_ms() const noexcept {
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - m_start).count();
}

template<class T>
auto duration_s(T&& callback) -> int64_t {
    auto sw = stopwatch();
    callback();
    return sw.elapsed_s();
}

template<class T>
auto duration_ms(T&& callback) -> int64_t {
    auto sw = stopwatch();
    callback();
    return sw.elapsed_ms();
}

} // namespace cool

