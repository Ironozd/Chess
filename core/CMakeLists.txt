cmake_minimum_required(VERSION 3.5.0)
project(Chess VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Chess src/main.cpp
    # Core Files #
    src/Core/Logger.cpp)

target_link_libraries(Chess PRIVATE spdlog::spdlog)

target_include_directories(Chess PRIVATE ${CMAKE_SOURCE_DIR}/deps/spdlog/include)