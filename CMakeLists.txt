cmake_minimum_required(VERSION 3.28)
project(JavaInterpreter)

set(CMAKE_CXX_STANDARD 17)

add_executable(JavaInterpreter main.cpp
        Diagram.cpp
        defs.h
        Diagram.h
        Diagram.cpp
        Scanner.cpp
        Scanner.h
        Semant.cpp
        Semant.h)
