cmake_minimum_required(VERSION 3.28)
project(Lab4 C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(src/include)

add_executable(lab.exe
        src/c/Service.c
        src/include/Codes.h
        src/c/objects/Stack.c
        src/include/objects/Stack.h
        src/c/objects/ListStack.c
        src/include/objects/ListStack.h
        src/c/primitives/List.c
        src/include/primitives/List.h
        src/c/IO.c
        src/include/IO.h
        src/include/primitives/StackElement.h
        src/c/primitives/Array.c
        src/include/primitives/Array.h
        src/c/primitives/PrimitiveInput.c
        src/include/primitives/PrimitiveInput.h
        src/main.c
        src/c/Experiments.c
        src/include/Experiments.h
)

#add_executable(unit.exe
#
#)
#
#target_include_directories(unit.exe
#        PRIVATE
#        /usr/local/lib
#)
#target_link_options(unit.exe
#        PRIVATE
#        /usr/local/lib/libcheck.a
#)

