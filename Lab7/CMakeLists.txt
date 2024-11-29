cmake_minimum_required(VERSION 3.29)
project(Lab7 C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(BinTree BinTree/src/BinRemove.c BinTree/src/BinTraverse.c BinTree/src/BinTree.c
        BinTree/src/BinTreeRotators.c
        BinTree/src/BinTreeRotators.h
        BinTree/src/BinAdd.c)
target_include_directories(BinTree PRIVATE BinTree)

add_library(HashMap
        HashMap/src/HashMapPublic.c
        HashMap/List/List.c
        HashMap/HashMapPrivate.h
        HashMap/Common.h
        HashMap/src/HashMapPrivate.c
)
target_include_directories(HashMap PRIVATE HashMap)


add_executable(Lab7.exe
        main.c
        BinTree/BinTree.h
)

add_dependencies(Lab7.exe BinTree HashMap)

add_executable(test.exe test_main.c)

add_dependencies(test.exe BinTree HashMap)

target_link_libraries(test.exe BinTree HashMap)