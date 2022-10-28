cmake_minimum_required(VERSION 3.10)
set(CMAKE_VERBOSE_MAKEFILE on)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(../Protos/grpc.cmake)

# project
project(snake VERSION 1.0)

include(sourcelist.cmake)


# Protobuf/Grpc source files
get_filename_component(PROTOS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Protos" ABSOLUTE)
set(PROTO_FILES
    ${PROTOS_DIR}/greet.proto
    ${PROTOS_DIR}/score.proto
)

# Generate file names for protoc output
foreach(PROTO ${PROTO_FILES})
    get_filename_component(PROTO_NAME "${PROTO}" NAME_WE)
    list(APPEND PROTO_GENERATED "${CMAKE_CURRENT_BINARY_DIR}/proto-gen/${PROTO_NAME}.pb.cc")
    list(APPEND PROTO_GENERATED "${CMAKE_CURRENT_BINARY_DIR}/proto-gen/${PROTO_NAME}.pb.h")
    list(APPEND PROTO_GENERATED "${CMAKE_CURRENT_BINARY_DIR}/proto-gen/${PROTO_NAME}.grpc.pb.cc")
    list(APPEND PROTO_GENERATED "${CMAKE_CURRENT_BINARY_DIR}/proto-gen/${PROTO_NAME}.grpc.pb.h")
endforeach()

# Invoke protoc against our proto files
add_custom_command(
      OUTPUT ${PROTO_GENERATED}
      COMMAND "${_PROTOBUF_PROTOC}"
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}/proto-gen"
           --cpp_out "${CMAKE_CURRENT_BINARY_DIR}/proto-gen"
           -I "${PROTOS_DIR}"
           --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
           ${PROTO_FILES}
      DEPENDS ${PROTO_FILES}
)

# Add protoc output to a library for consumption
add_library(myproto
    ${PROTO_GENERATED}
)
target_include_directories(myproto PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/proto-gen)

target_link_libraries(myproto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})
  
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)


# Enable multi-threaded compilation.
target_compile_options(${PROJECT_NAME} PRIVATE "/MP")

target_compile_options(${PROJECT_NAME} PRIVATE "/D_UNICODE")
target_compile_options(${PROJECT_NAME} PRIVATE "/DUNICODE")

target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PRIVATE
    engine
    myproto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
)
