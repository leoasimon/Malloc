#! /usr/bin/env python
# -*- coding: utf-8 -*-

import re
import subprocess as cmd
import os
import sys
import shlex

os.chdir(os.path.dirname(os.path.abspath(sys.argv[0])))

bin_folder = "bin/"
test_files = ["sandbox0.c", "sandbox1.c", "sandbox2.c", "sandbox3.c"]

bareme_test_files = ["bareme_test3.c", "bareme_test3_5.c", "bareme_test4.c", "bareme_test5.c"]
lib_inc = "../"

#############################################################
# run tests

def cmd_output(com):
    pipe = cmd.Popen(com, stdout=cmd.PIPE, stderr=cmd.PIPE)
    output, errput = pipe.communicate()
    return output, errput

def cmd_output_only(com):
    pipe = cmd.Popen(com, stdout=cmd.PIPE, stderr=cmd.PIPE)
    output, errput = pipe.communicate()
    return output

#############################################################
# make binary folder
com = "rm -rf " + bin_folder
cmd.call(com.split())
com = "mkdir " + bin_folder
cmd.call(com.split())

# compile sandboxes
for f in test_files:
    output_file = f[:-2]
    com = "sh ./run.sh ./" + bin_folder + output_file
    output = cmd_output_only(com.split())
    com = "gcc" + " -L../ " + " -Wall -Wno-unused-result -o " + bin_folder + output_file + " " + f + " -lft_malloc"
    cmd.call(com.split())
    com = "./" + bin_folder + output_file
    output, puterr = cmd_output(com.split())
    print("-----------------------------------\n")
    print("####### " + output_file + " #######\n")
    print(output)
    print("\033[91m" + puterr + "\033[0m\n")

# compile bareme tests
for f in bareme_test_files:
    output_file = f[:-2]
    print("##### " + output_file + " #####\n")
    if f != "bareme_test5.c":
        print("\033[91m" + "with stdlib" + "\033[0m\n")
        com = "gcc -o " + bin_folder + output_file + " " + f
        cmd.call(com.split())
        com = "./" + bin_folder + output_file
        output, puterr = cmd_output(com.split())
        print(output)

    print("\033[33m" + "our version" + "\033[0m\n")
    com = "gcc"+ " -L../ " + " -Wall -Wno-unused-result -o " + bin_folder + output_file + " " + f + " -lft_malloc"
    cmd.call(com.split())
    com = "./" + bin_folder + output_file
    output = cmd_output_only(com.split())
    print(output)
    
    # com = "gcc " + bin_folder + output_file + " " + f
    # cmd.call(com.split())
    # com = "./" + bin_folder + output_file
    # output = cmd_output_only(com.split())
    # print(output)

# com = "gcc"+ " -L../ " + " -Wall -Wno-unused-result -o " + bin_folder + "bareme_test5" + " " + "bareme_test5.c" + " -lft_malloc"
# cmd.call(com.split())
# com = "./" + bin_folder + "bareme_test5"
# output = cmd_output_only(com.split())
# print(output)
    

