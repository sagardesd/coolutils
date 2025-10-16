# cool::stopwatch

A lightweight stopwatch for measuring elapsed time in milliseconds or seconds.

## Overview

The `cool::stopwatch` class provides a simple way to measure elapsed time for performance testing or profiling code sections. It uses `std::chrono::steady_clock` internally and supports milliseconds and seconds precision.

## Usage

```cpp
#include <cool/stopwatch.hpp>
#include <thread>
#include <iostream>

int main() {
    cool::stopwatch sw;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << sw.elapsed_ms() << " ms elapsed\n";
    std::cout << sw.elapsed_s() << " s elapsed\n";
}
```

## API

| Function         | Description                                                                       |
| ---------------- | --------------------------------------------------------------------------------- |
| `stopwatch()`    | Constructs and starts the stopwatch.                                              |
| `restart()`      | Restart the stopwatch to measure a new interval.                                  |
| `elapsed_ms()`   | Returns the elapsed time in milliseconds.                                         |
| `elapsed_s()`    | Returns the elapsed time in seconds.                                              |
| `starttime_ms()` | Returns the start time of the stopwatch in milliseconds since steady clock epoch. |
| `starttime_s()`  | Returns the start time of the stopwatch in seconds since steady clock epoch.      |

## Measuring a Callback Execution

You can also measure the execution time of a callable using:

```cpp
#include <cool/stopwatch.hpp>
#include <thread>
#include <iostream>

int main() {
    auto ms = cool::duration_ms([]{
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    });

    auto s = cool::duration_s([]{
        std::this_thread::sleep_for(std::chrono::seconds(1));
    });

    std::cout << "Lambda took " << ms << " ms and " << s << " s\n";
}
```

## Notes

* Header-only: no linking required.
* Requires C++17 or higher.
* Provides a simple and clean API for timing operations.

