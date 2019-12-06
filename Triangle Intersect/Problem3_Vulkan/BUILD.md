# Building

The repository contains everything required to compile and build the examples on Windows using a C++ compiler that supports C++11. All required dependencies are included.

## <img src="./images/windowslogo.png" alt="" height="32px"> Windows

[![Build status](https://ci.appveyor.com/api/projects/status/abylymfyil0mhpx8?svg=true)](https://ci.appveyor.com/project/SaschaWillems/vulkan)

Use the provided CMakeLists.txt with [CMake](https://cmake.org) to generate a build configuration for your favorite IDE or compiler, e.g.:
```
cmake -G "Visual Studio 16 2019 Win64"
```
This project is going only for Windows. 
Preparation for the construction of the project:
- install Visual Studio 2019. This IDE is the best way to build a project.
- install ConUmu. Tests will be run through this command line.
- install CMake for Windows. It will be more convenient to open the application directly, rather than build the project from the command line.
- install VulkanSDK.

The Assembly part:

1. Open CMake (cmake-gui). In the top line enter the directory with the main CMakeList.txt : 
```
Where the source code: {PATH}/Problem3_Vulkan
Where to build the binaries: {PATH}/Problem3_Vulkan/build
```
Click "Configure" and then "Generate". Now you have a directory with an .exe file that you can run.

2. Go to the {PATH}/Problem3_Vulkan/build directory. Open the vulkanExamples.sln . 
In the window that opens, go to triangle folder, click right mouse-button and click "Assign to startup project". 
Now run the triangle.cpp by pressing ctrl+F7 or ctrl+F5. There should be a new folder in the build directory - bin.

3. Go to the bin/Debug folder. Move or copy the tests folder from 
{PATH}/Proble3_Vulkan directory in bin/Debug for convenience. 

4. Open ConEmu, go to {PATH}/Problem3_Vulkan/build/bin/Debug. You can now run tests.

5. Type the command:
```
triangle.exe < tests/{TEST_NAME}
```
Now the screen will appear a lot of triangles, which can be viewed in detail, moving with the mouse or TouchPad.