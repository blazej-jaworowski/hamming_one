cmake_minimum_required(VERSION 3.8)
project(hamming_one LANGUAGES CXX CUDA)

add_executable(main src/main.cpp)

set_target_properties(main PROPERTIES CUDA_SEPARABLE_COMPILATION ON)