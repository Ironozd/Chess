cmake_minimum_required(VERSION 3.5.0)
project(Chess VERSION 0.1.0 LANGUAGES C CXX)

enable_testing()

set(gtest_force_shared_crt on)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

find_package(Vulkan REQUIRED)

add_subdirectory(deps/glfw)
add_subdirectory(deps/glm)
add_subdirectory(deps/spdlog)
add_subdirectory(core)