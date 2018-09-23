RESET="\033[0m"
DARK="\033[132m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"
BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDWHITE="\033[1m\033[37m"
 

echo "\n$GREEN +++++++++  TEST0 ++++++++++ $RESET"
gcc -o test0 test0.c -g
echo "$BLUE ----------stdlib---------- $RESET"
/usr/bin/time -l ./test0

echo "$MAGENTA \n----------ours----------\n $RESET"
./run.sh /usr/bin/time -l ./test0

echo "\n$GREEN +++++++++  TEST1 ++++++++++ $RESET"
gcc -o test1 test1.c -g
echo "$BLUE ----------stdlib---------- $RESET"
/usr/bin/time -l ./test1

echo "$MAGENTA \n----------ours----------\n $RESET"
./run.sh /usr/bin/time -l ./test1

echo "\n$GREEN +++++++++  TEST2 (FREE) ++++++++++ $RESET"
gcc -o test2 test2.c -g
echo "$BLUE ----------stdlib---------- $RESET"
/usr/bin/time -l ./test2

echo "$MAGENTA \n----------ours----------\n $RESET"
./run.sh /usr/bin/time -l ./test2

echo "\n$GREEN +++++++++  TEST3 (REALLOC) ++++++++++ $RESET"
gcc -o test3 test3.c -L. -lft_block -g
echo "$BLUE ----------stdlib---------- $RESET"
./test3

echo "$MAGENTA \n----------ours----------\n $RESET"
./run.sh ./test3

echo "\n$GREEN +++++++++  TEST3.5 (REALLOC) ++++++++++ $RESET"
gcc -o test3_5 test3_5.c -g
echo "$BLUE ----------stdlib---------- $RESET"
./test3_5

echo "$MAGENTA \n----------ours----------\n $RESET"
./run.sh ./test3_5

echo "\n$GREEN +++++++++  TEST4 (FREE + REALLOC) ++++++++++ $RESET"
gcc -o test4 test4.c -g
echo "$BLUE ----------stdlib---------- $RESET"
./test4

echo "$MAGENTA \n----------ours----------\n $RESET"
./run.sh ./test4

echo "\n$GREEN +++++++++  TEST5 (FREE + REALLOC) ++++++++++ $RESET"
gcc -o test5 test5.c -L. -lft_block -g
echo "$BLUE ----------stdlib---------- $RESET"
echo "(NOT APPLICABLE)\n"

echo "$MAGENTA \n----------ours----------\n $RESET"
./run.sh ./test5