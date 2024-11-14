cmake_minimum_required(VERSION 3.28)
project(BinaryTrees C)
set(CMAKE_C_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

include_directories(src/include)

add_executable(BinaryTrees.exe
    src/main.c
        src/c/BinTree.c
        src/include/BinTree.h
)

