#!/bin/bash

find src -type f \( -name "*.c" -o -name "*.cc" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -exec clang-format -style=file:.clang-format -i {} \;
# find test -type f \( -name "*.c" -o -name "*.cc" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -exec clang-format -style=file:.clang-format -i {} \;
