# Style guide

The highest authority on code style is `clang-format` and `clangd`.
If they disagree with anything outlined below, their opinion takes
precedence.

If there is an unconsidered case, don't make up your own rules on
the fly. Instead, suggest it in a pull request editing this file.

## File management

Application source is fully contained within the `src` directory.
Entry point is located in the `main.cpp` file. We write
declarations in header files and implement them in source files.
If you use C++ templates, write the declaration in a header file
and implement it in a template implementation file, which you
include at the end of the header file.

`example.hpp`
```c++
#pragma once

template<typename T>
T add (T left, T right);

#include "example.tpp"
```

`example.tpp`
```c++
#pragma once

template<typename T>
T add (T left, T right) {
    return left + right;
}
```

At the start of every header file and every implementation
file, you should include the `#pragma once` directive.

### Unit tests

Unit tests should be located in a seperate file from the
feature their testing. They should be in the same directory.
The naming convention for a file containing unit tests for
a feature located in a `feature.cpp` file is `feature_test.cpp`.

### File names

C++ files are named in lower_snake_case, QML files are named
in CapitalizedCamelCase.

### File extensions

To keep the project consistent, stick to the following file
extensions:

 * `.cpp` - for C++ source files;
 * `.hpp` - for C++ header files;
 * `.tpp` - for C++ template implementation files.
 * `.qml` - for Qt objects definitions

To be continued...
