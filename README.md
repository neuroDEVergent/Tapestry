# Tapestry
Visual Novel Engine written in OpenGL with C/C++

## Build on Windows

### Before you start, you need to install some dependencies:

1. Install latest version of [CMake](https://cmake.org/download/)

2. Install vcpkg
```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
```

3. Install SDL2 and GLM using vcpkg:
```bash
vcpkg install sdl2 glm
```

### After installing dependencies, proceed with following:

1. Clone the repo:
```bash
git clone https://github.com/neuroDEVergent/Tapestry
```

2. Open the folder, then right click -> open in cmd


3. Tell CMake where vcpkg is:
```bash
cmake -B build -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
```

4. Build with
``` bash
cmake --build build
```

5. Run the .exe file loadted in: build -> Debug -> prog.exe
