#!/bin/bash

find src -type f \( -name "*.c" -o -name "*.cc" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -exec clang-format -style=file:.clang-format -i {} \;
find include -type f \( -name "*.c" -o -name "*.cc" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -exec clang-format -style=file:.clang-format -i {} \;
find test -type f \( -name "*.c" -o -name "*.cc" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -exec clang-format -style=file:.clang-format -i {} \;


find src -type f -name "*.cpp" -print0 | xargs -0 clang-tidy --config-file=.clang-tidy -p=build/ninja-release --quiet
find include -type f -name "*.h" -print0 | xargs -0 clang-tidy --config-file=.clang-tidy -p=build/ninja-release --quiet
# find include -type f -name "*.hpp" -print0 | xargs -0 clang-tidy --config-file=.clang-tidy -p=build/ninja-release --quiet
find test -type f -name "*.cpp" -print0 | xargs -0 clang-tidy --config-file=.clang-tidy -p=build/ninja-release --quiet