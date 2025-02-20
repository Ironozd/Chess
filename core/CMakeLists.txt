cmake_minimum_required(VERSION 3.5.0)
project(Chess VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Chess src/main.cpp
    # Core Files #
    src/Core/Logger.cpp
    src/Core/Engine.cpp
    # ChessLogic Files #
    src/ChessLogic/Board.cpp
    src/ChessLogic/Evaluation.cpp
    # ChessComponents Files #
    src/ChessComponents/Components.cpp
    src/ChessComponents/Bitboard.cpp
    src/ChessComponents/String.cpp
    src/ChessComponents/Turn.cpp
    # Window Files #
    src/Window/Window.cpp
    # Renderer Files #
    src/Renderer/Renderer.cpp
    src/Renderer/Instance.cpp
    src/Renderer/LogicalDevice.cpp
    src/Renderer/DebugMessenger.cpp
    src/Renderer/PhysicalDevice.cpp
    )

target_link_libraries(Chess PRIVATE spdlog::spdlog glfw Vulkan::Vulkan)

target_include_directories(Chess PRIVATE ${Vulkan_INCLUDE_DIRS})
target_include_directories(Chess PRIVATE ${CMAKE_SOURCE_DIR}/deps/spdlog/include)
target_include_directories(Chess PRIVATE ${CMAKE_SOURCE_DIR}/deps/glfw/include)
target_include_directories(Chess PRIVATE ${CMAKE_SOURCE_DIR}/deps/glm)
