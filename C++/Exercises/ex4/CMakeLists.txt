cmake_minimum_required(VERSION 3.16)
project(ex4)

set(CMAKE_CXX_STANDARD 17)

add_executable(ex4 main.cpp Matrix.cpp Activation.cpp Dense.h Dense.cpp MlpNetwork.cpp testing.cpp)