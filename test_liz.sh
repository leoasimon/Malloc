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
gcc -g -o test_liz test_liz.c -L. -lft_malloc -g
echo "$BLUE ----------stdlib---------- $RESET"
./test_liz

echo "$MAGENTA \n----------ours----------\n $RESET"
# ./run.sh ./test_liz