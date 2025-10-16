
#include <type_traits> 
#include "../stopwatch.hpp"
#include <cassert>
#include <thread>
#include <iostream>

using namespace cool;
inline void test_stopwatch() {
    using namespace std::chrono_literals;

    std::cout << "Running stopwatch tests...\n";

    // Test constructor and elapsed
    stopwatch sw;
    std::this_thread::sleep_for(120ms);
    int64_t elapsed1 = sw.elapsed_ms();
    assert(elapsed1 >= 100);

    // Test elapsed_s conversion
    int64_t elapsed_sec = sw.elapsed_s();
    assert(elapsed_sec == elapsed1 / 1000);

    // Test starttime
    int64_t start1 = sw.starttime_ms();
    assert(start1 > 0);
    int64_t start_sec = sw.starttime_s();
    assert(start_sec == start1 / 1000);

    // Test restart resets time
    std::this_thread::sleep_for(5ms);
    sw.restart();
    std::this_thread::sleep_for(50ms);
    int64_t elapsed2 = sw.elapsed_ms();
    assert(elapsed2 >= 40 && elapsed2 < 100);

    // Test duration_ms
    auto duration_ms_value = duration_ms([] {
        std::this_thread::sleep_for(150ms);
    });
    assert(duration_ms_value >= 140 && duration_ms_value <= 300);

    // Test duration_s
    auto duration_s_value = duration_s([] {
        std::this_thread::sleep_for(1100ms);
    });
    assert(duration_s_value == 1 || duration_s_value == 2); // tolerant rounding

    std::cout << "✅ All stopwatch tests passed ("
              << elapsed1 << " ms elapsed initially)\n";
}

int main(int argc, char* argv[]) {
    test_stopwatch();
    return 0;
}
