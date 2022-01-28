#! /bin/sh

./generate_sequences.sh
./run_tests.sh bit_sequences_*
rm bit_sequences_*