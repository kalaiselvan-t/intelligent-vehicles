cmake_minimum_required(VERSION 3.5)
project(v_opt)

add_library(v_opt v_opt.cpp rtGetInf.cpp rtGetNaN.cpp rt_nonfinite.cpp)