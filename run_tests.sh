#!/bin/bash
export DYLD_LIBRARY_PATH=$(pwd):$DYLD_LIBRARY_PATH

testsrc=$(pwd)/tests/src
testbin=$(pwd)/tests/bin

gcc -I. -I./libft/ $testsrc/sandbox.c -L/$(pwd) -lft_malloc -L libft -lft -o $testbin/sandbox

printf "\n------- Starting Tests -------"


printf "\n------- sandbox -------"
$testbin/sandbox

printf "\n------- test0 -------\n"
gcc -o $testbin/test0 $testsrc/test0.c
/usr/bin/time -l $testbin/test0

printf "\n------- test1 -------\n"
gcc -o $testbin/test1 $testsrc/test1.c
/usr/bin/time -l $testbin/test1