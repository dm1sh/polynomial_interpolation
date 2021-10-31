#!/bin/sh

gcc main.c
python input.py $1 | tee /dev/fd/2 | ./a.out | tee output.txt