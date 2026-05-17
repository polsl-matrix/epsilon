# epsilon

epsilon is a native Matrix client with a focus on performance. Minimalist
by design, it aims to deliver a seamless user experience - you won't even
know it's running.

# How to build the project?

## Debug mode

First, you have to install Qt version 6.11.0 from
[here](https://www.qt.io/development/download-qt-installer-oss).
Input the path to the installed Qt to the .env file.
Then, you will need to run `conan` to generate the necessary
CMake files. For that, run `conan install . -s build_type=Debug`.
A `build` directory and a `CMakeUserPresets.json` should now
appear in the root directory of the project. To run the generated
CMake preset, use the `cmake --preset conan-debug` command.
You may need to run it twice to get rid of the *Qt6 not found*
error. To then build the project, run `cmake --build --preset conan-debug`.
The built executable will be located at `build/Debug/epsilon.exe`.

**CAUTION!** If conan is complaining about missing binaries,
try running it with an additional `--build=missing` option.

## Release mode

Building in release mode looks similarly to building in debug mode.
After installing Qt, you need to run
`conan install . -s build_type=Release` to generate the CMake files.
Then, you run `cmake --preset conan-release`. Again, you may need
to run it twice. Finally, `cmake --build --preset conan-release`
should build the executable itself. It will be localted at
`build/Release/epsilon.exe`.

# Running tests

To run unit tests, you should first build the application in
debug mode. After that, run `cd build/Debug && ctest`. You should
now be seeing test results.
