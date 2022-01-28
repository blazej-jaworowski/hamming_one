#! /bin/sh

END=2
for var in "$@"
do
    echo $var
    for i in $(seq 0 $END)
    do
        build/main $i $var > output$i
    done
    for i in $(seq 1 $END)
    do
        build/verify output0 output$i
    done
    for i in $(seq 0 $END)
    do
        rm output$i
    done
done