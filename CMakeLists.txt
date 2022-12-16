cmake_minimum_required(VERSION 3.13)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(globalProject)

if(!MSVC)
    message("This project does not support the current configuration!")
    return()
endif()

add_subdirectory(src/2DEngine)
add_subdirectory(src/GameClient)