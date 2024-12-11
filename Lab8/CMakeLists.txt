cmake_minimum_required(VERSION 3.29)
project(Lab8 C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_C_STANDARD 23)

add_executable(Grapher.exe
        main.c
        src/Graph.c
        src/Graph.h
        src/Task.c
        src/Task.h
)
