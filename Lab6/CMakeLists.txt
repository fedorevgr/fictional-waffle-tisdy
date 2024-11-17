cmake_minimum_required(VERSION 3.28)
project(BinaryTrees C)
set(CMAKE_C_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

include_directories(src/include)

add_executable(BinaryTrees.exe
    src/main.c
        src/include/BinTree.h
        src/c/BinTree/BinTree.c
        src/c/BinTree/BinRemove.c
        src/c/BinTree/BinTraverse.c

        src/c/TreeOperationService.c
        src/include/TreeOperationService.h

        src/c/File.c
        src/include/File.h

        src/c/TreeServiceFunctions.c

        src/c/PrimitiveInput.c
        src/include/PrimitiveInput.h
)

