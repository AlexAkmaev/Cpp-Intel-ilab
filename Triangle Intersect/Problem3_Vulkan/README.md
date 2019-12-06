# Vulkan C++ examples and demos

A comprehensive collection of open source C++ examples for [Vulkan®](https://www.khronos.org/vulkan/), the new graphics and compute API from Khronos.

[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=BHXPMV6ZKPH9E)

## Table of Contents
+ [Cloning](#Cloning)
+ [Assets](#Assets)
+ [Building](#Building)
+ [Examples](#Examples)
    + [Basics](#Basics)
+ [Credits and Attributions](#CreditsAttributions)


## <a name="Cloning"></a> Cloning
This repository contains submodules for external dependencies, so when doing a fresh clone you need to clone recursively:

```
git clone --recursive https://github.com/AlexAkmaev/Cpp-Intel-ilab.git
``` 

Existing repositories can be updated manually:

```
git submodule init
git submodule update
```

## <a name="Building"></a> Building

The repository contains everything required to compile and build the examples on Windows using a C++ compiler that supports C++11.

See [BUILD.md](BUILD.md) for details on how to build in details.

## <a name="Examples"></a> Examples

### <a name="Basics"></a> Basics

#### [01 - Triangle](MAIN_PROJECT/triangle/)
Building a set of green triangles, which are repainted red at the intersection. This project is a modified copy of the Sasha Williams project referenced below. The changed fragments are marked with "//***CHANGED***BEG" and "//***CHANGED***END".List of modified files as well as those added to the original project:
1. In the folder shaders {PATH}/Problem3_Vulkan/shaders/*vert and shaders/*fraq are changed.
2. Triangle header files have been added to the MAIN_PROJECT folder.hpp and Geometry.hpp, which are inserted into the main triangle.cpp. In the latter, the main function as well as the methods of the VulkanExample class are changed.
3. The tests folder has been added to the {PATH}/Problem3_Vulkan folder.
4. After building the project, the build folder will appear in the {PATH}/Problem3_Vulkan folder, which is used to run the program and tests.


This project uses code from Vulkan Example Collection by SaschaWillems: https://github.com/SaschaWillems/Vulkan

The MIT License (MIT)

Copyright (c) 2016 Sascha Willems

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.