#include <stdlib.h>

int      main()
{
   int   i;
   char  *addr;

   i = 0;
   while (i < 1024)
   {
      i++;
   }
   return (0);
}
//  gcc -o test0 test0.c
//  /usr/bin/time -l ./test0
//      0.00 real 0.00 user 0.00 sys
//    491520 maximum resident set size
//       0 average shared memory size
//       0 average unshared data size
//       0 average unshared stack size
//      139 page reclaims
//       0 page faults
//       0 swaps
//       0 block input operations
//       0 block output operations
//       0 messages sent
//       0 messages received
//       0 signals received
//       0 voluntary context switches
//       1 involuntary context switches