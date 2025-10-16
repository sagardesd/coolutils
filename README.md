# cooltools 🧊

**cooltools** is a modern C++ header-only library providing small, reusable utilities for everyday development.

## Features

* 🕒 `cool::stopwatch` — measure elapsed time. [Documentation](docs/stopwatch.md)
* 📄 `cool::txtfilestream` — iterate over text files line by line. [Documentation](docs/txtfilestream.md)
* 📅 `cool::datetime` — date/time helpers (coming soon)

## Usage

Clone and include the `include/` directory:

```bash
git clone https://github.com/yourname/cooltools.git
```

Compile your project with the include path:

```bash
g++ -std=c++17 -I cooltools/include main.cpp -o main
```

### Example

```cpp
#include <cool/stopwatch.hpp>
#include <thread>
#include <iostream>

int main() {
    cool::stopwatch sw;
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    std::cout << "Elapsed: " << sw.elapsed_ms() << " ms\n";
}
```

## Documentation

Each header has its own documentation page in [`docs/`](docs/):

* [stopwatch.md](docs/stopwatch.md)
* [txtfilestream.md](docs/txtfilestream.md)
* datetime.md (coming soon)

## Installation

Simply include the `include/` folder in your project:

```cpp
#include <cool/stopwatch.hpp>
#include <cool/txtfilestream.hpp>
```

No linking required as this is a header-only library.

## Note:
Please compile with cpp standard >= C++11,14,17

## License

This project is licensed under the MIT License.

