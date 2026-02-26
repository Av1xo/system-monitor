cmake_minimum_required(VERSION 3.16)
project(agent LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(agent
    src/main.cpp
    src/provider.cpp
    src/platform/linux/linux.cpp
)

target_include_directories(agent PRIVATE includes)

if (WIN32)
    target_sources(agent PRIVATE src/platform/windows.cpp)
endif()