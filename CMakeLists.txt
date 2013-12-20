cmake_minimum_required(VERSION 2.8)
project(gamma)

set(CMAKE_BUILD_TYPE Debug)

include_directories(.)
add_executable(vector tests/vector.cpp)
add_executable(sizes tests/sizes.cpp)
add_executable(matrix tests/matrix.cpp)