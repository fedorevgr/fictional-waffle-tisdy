cmake_minimum_required(VERSION 3.28)
project(Lab5 C)

set(CMAKE_C_STANDARD 23)

include_directories(src/include)

add_executable(Lab5 src/main.c
        src/c/ArrayQueue.c
        src/c/ListQueue.c
        src/c/Service.c
        src/c/QueueElement.c
        src/c/PrimitiveInput.c
)
