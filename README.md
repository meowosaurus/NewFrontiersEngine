# NewFrontiersEngine

## Requirements
- OpenGL 3.3
- cmake
- CLion (you can use any other IDE, but I only provide instructions for CLion)
- Qt 5.15.2

## Deploy

### Windows
1. Install Qt 5.15.2
2. Open ```NewFrontiersEngine/``` as CLion project
3. Edit ```NewFrontiersEngine/CMakeLists.txt``` and change the path to your Qt installation on your plattform. 
   1. It's important to link to ```Qt/5.15.2/<Compiler>/lib/cmake```
   2. Example: ```Qt/5.15.2/mingw81_64/lib/cmake```
4. Reload CMake Project
5. Build & Run

### Linux
1. Install Qt 5.15.2
2. Install the following packages ```sudo apt install build-essential libgl1-mesa-dev cmake```
3. Open ```NewFrontiersEngine/``` as CLion project
4. Edit ```NewFrontiersEngine/CMakeLists.txt``` and change the path to your Qt installation on your plattform. 
   1. It's important to link to ```Qt/5.15.2/<Compiler>/lib/cmake```
   2. Example: ```Qt/5.15.2/gcc_64/lib/cmake```
5. Reload CMake Project
6. Build & Run
