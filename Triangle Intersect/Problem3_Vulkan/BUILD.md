# Building

The repository contains everything required to compile and build the examples on Windows using a C++ compiler that supports C++11. All required dependencies are included.

## <img src="./images/windowslogo.png" alt="" height="32px"> Windows

[![Build status](https://ci.appveyor.com/api/projects/status/abylymfyil0mhpx8?svg=true)](https://ci.appveyor.com/project/SaschaWillems/vulkan)

Use the provided CMakeLists.txt with [CMake](https://cmake.org) to generate a build configuration for your favorite IDE or compiler, e.g.:
```
cmake -G "Visual Studio 16 2019 Win64"
```
Also download ConEmu for Windows to run tests in /examples directory by command:
```
triangle.exe < tests/{TEST_NAME}
```
