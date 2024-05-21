#!/bin/bash

files=$(find . -name '*.c')

for file in $files; do
    clang-format -i $file
done