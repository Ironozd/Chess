# Vulkan Chess Engine [Work in Progress]

## Overview
This project will implement a Chess engine that uses Vulkan Compute API to conduct its search algorithm. The project will introduce a core engine library consisting of all chess functions and renderer functions.

## Build Instructions
### Prerequisites
- [Vulkan SDK](https://vulkan.lunarg.com/sdk/home)
- CMake
- C++ compiler; MinGW
- VS Code (Optional)
### Windows
First of all, clone the git repository including its submodules.
```
git clone --recursive https://github.com/Ironozd/Chess.git
```
You can then directly open the folder in VS code and configure the project using; `CTRL+SHIFT+P` then by typing "CMake: Configure".
Alternatively, you can also:
Create a new folder called "build",
```
mkdir build
```
Then navigate to the directory,
```
cd build
```
Then run CMake using;
```
cmake ..
```
Finally you can build the project with the command;
```
cmake --build .
```
Since the project is under development, there are no difference in building in DEBUG or RELEASE mode (except standard optimizations and symbol managements). Instructions will be changed upon later releases.
You can still build the project in release mode with;
```
cmake -DCMAKE_BUILD_TYPE=Release ..
```
## What will the project look like in the future?
- Core project will be a static library, consisting of core engine files for both Chess engine and renderer.
- 2 executables; A Chess Game (which will render graphics using Vulkan and Window using GLFW), A Lichess Integration App (A console view that will support UCI and communication with lichess.org).

### Future Project Structure
    - /
        - core/
            - src/ (will hold all functionality)
        - game/
            - src/ (will only hold configuration and UI settings)
        - lichess
            - src/ (will only hold configuration)

## Unique Features
- Search algorithm is conducted through Vulkan Compute API. (not implemented yet)
- Lichess integration through lichess-bot. (not implemented yet)
- The core library will be designed so that it will support other integrations to the chess engine.

## Dependencies
- GLFW Window API : Window
- Vulkan API : Renderer to display the visual representation of the game, compute API to increase search algorithm performance.
- GLM : Math library.
- spdlog : For performance-critical logging at runtime