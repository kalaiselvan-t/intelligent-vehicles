cmake_minimum_required(VERSION 3.5)
project(pass_primitive)

add_library(pass_primitive pass_primitive.cpp rt_nonfinite.cpp rtGetInf.cpp rtGetNaN.cpp)

