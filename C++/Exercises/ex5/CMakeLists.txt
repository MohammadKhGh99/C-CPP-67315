cmake_minimum_required(VERSION 3.16)
project(ex5)

set(CMAKE_CXX_STANDARD 17)

add_executable(ex5 myMain.cpp RecommenderSystem.h RecommenderSystem.cpp temp.cpp RecommendByCF.cpp RecommendByContent.cpp main.cpp ibrahem.h ibrahemC.cpp)