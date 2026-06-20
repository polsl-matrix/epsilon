#!/bin/bash
find . -name "*.cpp" -o -name "*.h" -o -name "*.qml" | xargs clang-format -i
