cmake_minimum_required(VERSION 3.28)
project(Lab2 C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Lab2 src/main.c
        src/include/common/ExitCodes.h
        src/include/common/Macros.h
        src/c/Car.c
        src/include/Car.h
        src/c/IO/input.c
        src/include/IO/input.h
        src/c/IO/output.c
        src/include/IO/output.h
        src/c/Table.c
        src/include/Table.h
        src/c/Sorting.c
        src/include/Sorting.h
        src/c/utils.c
        src/include/IO/CarPrompts.h
        src/c/Service.c
        src/include/Service.h
)

set_target_properties(Lab2
        PROPERTIES OUTPUT_NAME "app.exe"
)


