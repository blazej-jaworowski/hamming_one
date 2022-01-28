cmake_minimum_required(VERSION 3.8)
project(hamming_one LANGUAGES CXX CUDA)

add_executable(main src/main.cpp src/HOne.h
                    src/HOCBadEncoding.h src/HOCBadEncoding.cpp
                    src/HOCGoodEncoding.h src/HOCGoodEncoding.cpp
                    src/HOGPU.cuh src/HOGPU.cu)
add_executable(test_generator src/test_generator.cpp)

set_property(TARGET main test_generator PROPERTY CXX_STANDARD 17)

set_target_properties(main PROPERTIES CUDA_SEPARABLE_COMPILATION ON)