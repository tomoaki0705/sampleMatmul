cmake_minimum_required(VERSION 2.8)

set(TARGET_NAME oclMatMul)

project(${TARGET_NAME})

add_executable(matMulSimple simpleMatmul.cpp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(matMulSimple ${OpenCV_LIBS})

