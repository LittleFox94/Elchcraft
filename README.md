# Elchcraft

Win32: [![Build Status](https://praios.lf-net.org/jenkins/buildStatus/icon?job=Elchcraft_Win32)](https://praios.lf-net.org/jenkins/job/Elchcraft_Win32) Win64: [![Build Status](https://praios.lf-net.org/jenkins/buildStatus/icon?job=Elchcraft_Win64)](https://praios.lf-net.org/jenkins/job/Elchcraft_Win64)

Coding a game just for fun. Asked on twitter for ideas, got two answers: "It has to contain Elks!" and "Did someone say minecraft already?".
So this will be something with elks and minecraft - don't know anything else yet.

## Technical

It's done using GLFW3, GLM and GLEW using OpenGL 3.3 Core Profile. It's the first time I'm using shaders, so it may be somewhat crazy/bad.

Because I love coding game-engines, the one here is completely self-developed. I try to make it as great and reusable as possible.

## Jenkins

Builds for Win32 and Win64 are done automagically. Maybe I'll add debian-builds. You can find them in my jenkins:
https://praios.lf-net.org/jenkins/

## Building

### Get glew for your platform.
* Debian: sudo apt-get install libglew-dev
* Other linux: should be similiar
* Windows: good luck. At least visual studio and the binaries from glew.sourceforge.net work. No MinGW.

### Clone the repo and the submodules
```
git clone https://github.com/LittleFox94/Elchcraft.git elchcraft && cd elchcraft
git submodule update --init
```

### Build and run
```
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=install ..
make -j4 install
./install/bin/elchcraft
```
