# cool::txtfilestream

A lightweight header-only utility for reading text files line by line using C++ iterators.

## Overview

This header provides classes to iterate over lines in a text file as a standard C++ input iterator. It is designed to be simple, reusable, and compatible with range-based for loops.

## Classes

### `cool::Line`

Represents a single line from a text stream.

#### Member Functions

| Function                      | Description                                                      |
| ----------------------------- | ---------------------------------------------------------------- |
| `size()`                      | Returns the length of the current line.                          |
| `readNextLine(std::istream&)` | Reads the next line from the given input stream into the object. |
| `operator*()`                 | Returns the current line as a `std::string`.                     |

### `cool::FileIterator`

Input iterator for reading lines from a stream.

#### Member Types

| Type                | Description               |
| ------------------- | ------------------------- |
| `value_type`        | `Line`                    |
| `pointer`           | Pointer to `Line`         |
| `reference`         | Reference to `Line`       |
| `iterator_category` | `std::input_iterator_tag` |
| `difference_type`   | `std::size_t`             |

#### Constructors

| Constructor                   | Description                                                   |
| ----------------------------- | ------------------------------------------------------------- |
| `FileIterator(std::istream&)` | Creates an iterator starting at the first line of the stream. |
| `FileIterator()`              | Creates an end iterator.                                      |

#### Operators

| Operator          | Description                              |
| ----------------- | ---------------------------------------- |
| `operator++()`    | Advances the iterator to the next line.  |
| `operator++(int)` | Postfix increment.                       |
| `operator*()`     | Returns the current `Line`.              |
| `operator->()`    | Returns a pointer to the current `Line`. |
| `operator==()`    | Checks if two iterators are equal.       |
| `operator!=()`    | Checks if two iterators are not equal.   |

### `cool::IteratorRange`

Provides a range wrapper over a stream to allow usage in range-based for loops.

#### Member Functions

| Function  | Description                                                                      |
| --------- | -------------------------------------------------------------------------------- |
| `begin()` | Returns a `FileIterator` pointing to the first line of the stream.               |
| `end()`   | Returns a default-constructed `FileIterator` representing the end of the stream. |

## Usage

```cpp
#include <fstream>
#include <iostream>
#include "cool/txtfilestream.hpp"

int main(int argc, char* argv[]) {
    std::ifstream stream(argv[1]);
    for (auto& line: cool::IteratorRange(stream)) {
        std::cout << *line << std::endl;
    }
}
```

## Notes

* Header-only: no linking required.
* Compatible with C++11 and later.
* Useful for line-by-line processing of large files without loading the entire file into memory.

