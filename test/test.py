#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8

import re
import subprocess as cmd
import os
import sys
import shlex

os.chdir(os.path.dirname(os.path.abspath(sys.argv[0])))

bin_folder = "bin/"
test_files = ["test0.c", "test1.c", "test2.c", "test3.c",
        "test3_5.c", "test4.c"]
lib_inc = "../"

#############################################################
# functions
def page_reclaims(prog):
    com = "./run.sh /usr/bin/time -l ./" + bin_folder + prog
    pipe = cmd.Popen(com.split(), stdout=cmd.PIPE, stderr=cmd.PIPE)
    output, errput = pipe.communicate()
    m = re.search('([0-9]+?)[ \t]+page[ \t]+reclaims', errput)
    if m:
        found = m.group(1)
        return int(found)
    return ""

def cmd_output(com):
    pipe = cmd.Popen(com, stdout=cmd.PIPE, stderr=cmd.PIPE)
    output, errput = pipe.communicate()
    return output, errput

def cmd_output_only(com):
    pipe = cmd.Popen(com, stdout=cmd.PIPE, stderr=cmd.PIPE)
    output, errput = pipe.communicate()
    return output

def cmp_output(prog, to_compare):
    com = "./run.sh ./" + bin_folder + prog
    output = cmd_output(com.split())
    if output[0] == to_compare:
        print("OK")
    else:
        print("ERROR")

#############################################################
# compilation
com = "rm -rf " + bin_folder
cmd.call(com.split())
com = "mkdir " + bin_folder
cmd.call(com.split())

for f in test_files:
    output_file = f[:-2]
    com = "gcc -Wno-unused-result -o " + bin_folder + output_file + " " + f + " -I " + lib_inc
    cmd.call(com.split())

#############################################################
# malloc
pr0 = page_reclaims("test0")
pr1 = page_reclaims("test1")
pr2 = page_reclaims("test2")
pr1c = pr1 - pr0
print("#####Test malloc")
print("Page reclaims for test0 (NO MALLOC, initial PR):     " + str(pr0))
print("Page reclaims for test1 (WITH MALLOC, PR Full Load): " + str(pr1))
print("Page reclaims for test2:                             " + str(pr2))
print("\nFor test1 (minus test0 for compensation) the PR is:  " + str(pr1c) + " --> Score (out of 5):\n")
if pr1c < 255:
    print("0/5\nmoins de 255 pages, la mémoire réservée est insuffisante: 0")
elif pr1c > 1023:
    print("1/5\n1023 pages et plus, le malloc fonctionne mais consomme une page minimum à chaque allocation: 1")
elif pr1c > 513 and pr1c < 1022:
    print("2/5\nentre 513 pages et 1022 pages, le malloc fonctionne mais l'overhead est trop important: 2")
elif pr1c > 313 and pr1c < 512:
    print("3/5\nentre 313 pages et 512 pages, le malloc fonctionne mais l'overhead est très important: 3")
elif pr1c > 273 and pr1c < 312:
    print("4/5\nentre 273 pages et 312 pages, le malloc fonctionne mais l'overhead est important: 4")
elif pr1c > 255 and pr1c < 272:
    print("5/5\nentre 255 et 272 pages, le malloc fonctionne et l'overhead est raisonnable")
print("")
#############################################################
# Free
print("#####Test free")
print("Page reclaims for test0 (NO MALLOC, initial PR):     " + str(pr0))
print("Page reclaims for test2:                             " + str(pr2))
print("delta PR between test2 and test0:                    " + str(pr2 - pr0))
if (pr2 - pr0) <= 3:
    print("Max 3 page reclaim more than test0. The free is working as expected !")
elif pr2 < pr1:
    print("Free is functioning.")
else:
    print("The free does not work.")
print("");
#############################################################
# Realloc
print("#####Test realloc")
cmp_output("test3", "Bonjours\nBonjours\n")

#############################################################
# Realloc ++
print("#####Test realloc++")
cmp_output("test3_5", "Bonjours\nBonjours\n")

#############################################################
# Errors
print("#####Test errors")
cmp_output("test4", "Bonjours\n")

#############################################################
# show_alloc_mem
# For this test to work, you need to have the libmalloc_darwin...
# in the current directory.
print("#####Test print_alloc_mem")
com = "gcc"+ " -L../ " + " -Wall -Wno-unused-result -o " + bin_folder + "test5" + " " + "test5.c" + " -lft_malloc"
cmd.call(com.split())
com = "./" + bin_folder + "test5"
output = cmd_output_only(com.split())
print(output)

