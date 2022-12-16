set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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

target_compile_options(${PROJECT_NAME} PRIVATE "/D_UNICODE")
target_compile_options(${PROJECT_NAME} PRIVATE "/DUNICODE")

# Enable severe warnings.
target_compile_options(${PROJECT_NAME} PRIVATE "/W1")

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_include_directories(${PROJECT_NAME} PUBLIC include)