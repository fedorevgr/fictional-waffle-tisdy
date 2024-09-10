cmake_minimum_required(VERSION 3.28)
project(Lab1 C)

set(CMAKE_C_STANDARD 23)

add_executable(Lab1 main.c
        src/IO/graphics.h
        src/IO/graphics.c
        src/IO/input.c
        src/IO/input.h
        src/mathing.c
        src/mathing.h
        src/Types.h
        src/IO/output.c
        src/IO/output.h
        src/IO/Validation/Validation.c
        src/IO/Validation/Validation.h
        src/IO/Validation/StringUtils.c
        src/IO/Validation/StringUtils.h
        src/Types.c
        src/IO/IO.h
)

add_executable(tests test/InputTests.c
        test/InputTests.h
        src/IO/graphics.h
        src/IO/graphics.c
        src/IO/input.c
        src/IO/input.h
        src/mathing.c
        src/mathing.h
        src/Types.h
        test/utils/ValidationTests.c
        test/utils/ValidationTests.h
        src/IO/Validation/StringUtils.c
        src/IO/Validation/StringUtils.h
        src/IO/Validation/Validation.c
        src/IO/Validation/Validation.h
        RunTests.c
        test/MathingTest.c
        test/MathingTest.h
        src/Types.c
        test/Tests.h
)

target_compile_definitions(
        Lab1
        PRIVATE
        EXP_PRINT
)

#
#target_compile_definitions(tests
#        PRIVATE
#        TO_START=6
#)
