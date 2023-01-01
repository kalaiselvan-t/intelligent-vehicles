cmake_minimum_required(VERSION 3.5)
project(primitives)

add_library(primitives primitives.cpp rtGetInf.cpp rtGetNaN.cpp rt_nonfinite.cpp)