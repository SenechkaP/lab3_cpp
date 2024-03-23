cmake_minimum_required(VERSION 3.26)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab3 main.cpp
        man.h
        man.cpp
        doctor.h
        doctor.cpp
        main.h
        funcs.cpp
        funcs.h)
