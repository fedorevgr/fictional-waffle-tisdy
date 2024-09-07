cmake_minimum_required(VERSION 3.28)
project(Lab1 C)

set(CMAKE_C_STANDARD 23)

add_executable(Lab1 main.c
        src/graphics.h
        src/graphics.c
        src/input.c
        src/input.h
        src/mathing.c
        src/mathing.h
        src/Types.h
        src/output.c
        src/output.h
        src/Validation/Validation.c
        src/Validation/Validation.h
        src/Validation/StringUtils.c
        src/Validation/StringUtils.h
        src/Types.c)

add_executable(tests test/InputTests.c
        test/InputTests.h
        src/graphics.h
        src/graphics.c
        src/input.c
        src/input.h
        src/mathing.c
        src/mathing.h
        src/Types.h
        test/utils/ValidationTests.c
        test/utils/ValidationTests.h
        src/Validation/StringUtils.c
        src/Validation/StringUtils.h
        src/Validation/Validation.c
        src/Validation/Validation.h
        RunTests.c
)
