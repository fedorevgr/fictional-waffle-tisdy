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
        src/types.h
        src/output.c
        src/output.h
        src/utils/validation.c
        src/utils/validation.h
        src/utils/StringUtils.c
        src/utils/StringUtils.h)

add_executable(tests test/InputTests.c
        test/InputTests.h
        src/graphics.h
        src/graphics.c
        src/input.c
        src/input.h
        src/mathing.c
        src/mathing.h
        src/types.h
        test/utils/ValidationTests.c
        test/utils/ValidationTests.h
        src/utils/StringUtils.c
        src/utils/StringUtils.h
        src/utils/validation.c
        src/utils/validation.h
        RunTests.c
)
