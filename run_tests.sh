#!/bin/bash

testsrc=$(pwd)/test
testbin=$(pwd)/test/bin

mkdir $testsrc/bin
export DYLD_LIBRARY_PATH=$(pwd):$DYLD_LIBRARY_PATH

gcc -I. -I./libft/ $testsrc/sandbox.c -L/$(pwd) -lft_malloc -L libft -lft -o $testbin/sandbox

printf "\n------- Starting Tests -------"


printf "\n------- sandbox -------\n"
$testbin/sandbox

# printf "\n------- test0 -------\n"
# gcc -o $testbin/test0 $testsrc/test0.c
# /usr/bin/time -l $testbin/test0

# printf "\n------- test1 -------\n"
# gcc -o $testbin/test1 $testsrc/test1.c
# /usr/bin/time -l $testbin/test1

# printf "\n------- test2 -------\n"
# gcc -o $testbin/test2 $testsrc/test2.c
# /usr/bin/time -l $testbin/test2