#!/bin/bash
export DYLD_LIBRARY_PATH=$(pwd):$DYLD_LIBRARY_PATH

testsrc=$(pwd)/tests/src
testbin=$(pwd)/tests/bin

gcc -I. -I./libft/ $testsrc/test1.c -L/$(pwd) -lft_malloc -L libft -lft -o $testbin/test1
printf "\n------- Starting Tests -------"
$testbin/test1