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
git clone --recursive https://github.com/SaschaWillems/Vulkan.git
``` 

Existing repositories can be updated manually:

```
git submodule init
git submodule update
```

## <a name="Assets"></a> Assets
Many examples require assets from the asset pack that is not part of this repository due to file size. A python script is included to download the asset pack that. Run

    python download_assets.py

from the root of the repository after cloning or see [this](data/README.md) for manual download.

## <a name="Building"></a> Building

The repository contains everything required to compile and build the examples on <img src="./images/windowslogo.png" alt="" height="22px" valign="bottom"> Windows using a C++ compiler that supports C++11.

See [BUILD.md](BUILD.md) for details on how to build for the different platforms.

## <a name="Examples"></a> Examples

### <a name="Basics"></a> Basics

#### [01 - Triangle](examples/triangle/)
Basic and verbose example for getting a colored triangle rendered to the screen using Vulkan. This is meant as a starting point for learning Vulkan from the ground up. A huge part of the code is boilerplate that is abstracted away in later examples.

## <a name="CreditsAttributions"></a> Credits and Attributions
See [CREDITS.md](CREDITS.md) for additional credits and attributions.
