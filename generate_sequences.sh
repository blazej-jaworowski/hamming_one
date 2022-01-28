#! /bin/sh

build/test_generator 10000 1000 1000
build/test_generator 20000 1000 2000
build/test_generator 40000 1000 4000
build/test_generator 80000 1000 8000
build/test_generator 160000 1000 16000

build/test_generator 10000 2000 1000
build/test_generator 20000 2000 2000
build/test_generator 40000 2000 4000
build/test_generator 80000 2000 8000
build/test_generator 160000 2000 16000