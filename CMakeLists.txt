cmake_minimum_required(VERSION 2.8)

set(TARGET_NAME oclMatMul)

project(${TARGET_NAME})

add_executable(matMulSimple simpleMatmul.cpp)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wno-psabi")
endif()
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(matMulSimple ${OpenCV_LIBS})

