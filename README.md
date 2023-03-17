# Intel-AMX-experiment

Demo of Intel AMX. Tested on Ubuntu 22.04.

Prerequisites:
- processor with AMX support
- Linux kernel 5.16+
- gcc 11+
- binutils 2.36+

# Build
```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=[Release|Debug] ..
cmake --build .
```
Debug build contains additional debug prints.

# Test
```
ctest
```
