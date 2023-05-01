#!/bin/bash
for i in $(seq 0 20);do
    ./q2
    diff -s squaresort.txt circlesort.txt
done