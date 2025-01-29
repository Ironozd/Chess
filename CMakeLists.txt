cmake_minimum_required(VERSION 3.5.0)
project(Chess VERSION 0.1.0 LANGUAGES C CXX)

find_package(Vulkan REQUIRED)

add_subdirectory(deps/glfw)
add_subdirectory(deps/glm)
add_subdirectory(deps/spdlog)
add_subdirectory(core)