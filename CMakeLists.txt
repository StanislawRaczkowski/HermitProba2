cmake_minimum_required(VERSION 3.29)
project(HermitProba2 C)

set(CMAKE_C_STANDARD 23)
add_executable(HermitProba2 main.c DividedDifference.c
        generateHermitPolynomial.c
        DisplayData.c)

