cmake_minimum_required(VERSION 3.28)
project(Lab3 C)

set(CMAKE_C_STANDARD 11)

include_directories(src/include)

add_executable(Lab3
        src/main.c
        src/c/objects/Matrix.c
        src/include/objects/Matrix.h
        src/c/objects/Vector.c
        src/include/objects/Vector.h
        src/include/Codes.h
        src/c/Input.c
        src/include/Input.h
        src/c/Arrays.c
        src/include/Arrays.h
        src/c/Meth.c
        src/c/Meth.h
)

add_executable(HandTest
        src/c/objects/Matrix.c
        src/include/objects/Matrix.h
        src/c/objects/Vector.c
        src/include/objects/Vector.h
        src/include/Codes.h
        src/c/Input.c
        src/include/Input.h
        src/c/Arrays.c
        src/include/Arrays.h
        testing/Dump.c
        src/c/Meth.c
        src/c/Meth.h
)

include_directories(/usr/local/include)
include_directories(testing)

add_compile_options(-g -O0)

add_link_options(/usr/local/lib/libcheck.a)

add_executable(TestMatrix
        src/c/objects/Matrix.c
        testing/RealMatrixTests.c
        src/c/Arrays.c
        src/c/Input.c
        src/c/Meth.c
        src/c/Meth.h
)

add_executable(TestArray
        src/c/Arrays.c
        testing/ArraysTests.c
)

add_executable(AllTests
        testing/Unit.c

        src/c/objects/Matrix.c
        src/c/Arrays.c
        src/c/Input.c

        testing/RealMatrixTests.c
        testing/ArraysTests.c
        src/c/Meth.c
        src/c/Meth.h
)
