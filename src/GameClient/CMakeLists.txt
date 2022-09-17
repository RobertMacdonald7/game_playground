cmake_minimum_required(VERSION 3.10)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# project
project(snake VERSION 1.0)

include(sourcelist.cmake)
add_executable(${PROJECT_NAME} ${SOURCES})

# Enable multi-threaded compilation.
target_compile_options(${PROJECT_NAME} PRIVATE "/MP")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MDd")
else()
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD")
endif()

target_compile_options(${PROJECT_NAME} PRIVATE "/D_UNICODE")
target_compile_options(${PROJECT_NAME} PRIVATE "/DUNICODE")

target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PUBLIC engine)