cmake_minimum_required(VERSION 3.17)
project(examC C)

set(CMAKE_C_STANDARD 99)

add_executable(examC SpreaderDetectorBackend.c SpreaderDetectorParams.h mosaLab6.c square.h square.c main.c)