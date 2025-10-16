#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <cstdint>

namespace cool::datetime {

inline auto now_ms() noexcept -> int64_t {
	struct timeval tp;
	::gettimeofday(&tp, nullptr);
	return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

inline auto now_ns() noexcept -> int64_t {
	struct timespec tp;
	(void)::clock_gettime(CLOCK_REALTIME, &tp);
	return (int64_t)(tp.tv_sec) * (int64_t)1000000000 + (int64_t)(tp.tv_nsec);
}

inline auto now() noexcept -> int64_t {
	struct timeval tp;
	::gettimeofday(&tp, nullptr);
	return tp.tv_sec;
}

inline bool force_timezone_to_utc() noexcept {
	if (::setenv("TZ", "UTC", 1) == 0) {
		::tzset();
		return true;
	}
	return false;
}
} // cool::datetime
