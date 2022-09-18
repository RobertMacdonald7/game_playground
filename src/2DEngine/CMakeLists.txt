cmake_minimum_required(VERSION 3.10)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# project
project(engine VERSION 1.0)

include(sourcelist.cmake)
add_library(${PROJECT_NAME} SHARED
    ${SOURCES}
    ${HEADERS}
    ${PUBLIC_INCLUDES}
)

target_compile_definitions(${PROJECT_NAME} PRIVATE "ENGINE_2D_EXPORTS")

# Enable multi-threaded compilation.
target_compile_options(${PROJECT_NAME} PRIVATE "/MP")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MDd")
else()
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD")
endif()

target_compile_options(${PROJECT_NAME} PRIVATE "/D_UNICODE")
target_compile_options(${PROJECT_NAME} PRIVATE "/DUNICODE")

# Enable severe warnings.
target_compile_options(${PROJECT_NAME} PRIVATE "/W1")

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_include_directories(${PROJECT_NAME} PUBLIC include)