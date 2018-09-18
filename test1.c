#include <stdlib.h>

int      main()
{
   int   i;
   char  *addr;

   i = 0;
   while (i < 1024)
   {
      addr = (char*)malloc(1024);
      addr[0] = 42;
      i++;
   }
   return (0);
}
// $&gt; gcc -o test1 test1.c
// $&gt; /usr/bin/time -l ./test1
//           0.00 real 0.00 user 0.00 sys
//        1544192 maximum resident set size
//            0 average shared memory size
//            0 average unshared data size
//            0 average unshared stack size
//           396 page reclaims
//            0 page faults
//            0 swaps
//            0 block input operations
//            0 block output operations
//            0 messages sent
//            0 messages received
//            0 signals received
//            0 voluntary context switches
//            1 involuntary context switches


// $./run.sh /usr/bin/time -l ./test1
//      0.00 real 0.00 user 0.00 sys
//   4902912 maximum resident set size
//      0 average shared memory size
//      0 average unshared data size
//      0 average unshared stack size
//    1238 page reclaims
//      0 page faults
//      0 swaps
//      0 block input operations
//      0 block output operations
//      0 messages sent
//      0 messages received
//      0 signals received
//      0 voluntary context switches
//      2 involuntary context switches
// $


// Comptez le nombre de page utilisées et ajustez la note comme suit:
// - moins de 255 pages, la mémoire réservée est insuffisante: 0
// - 1023 pages et plus, le malloc fonctionne mais consomme une page minimum à chaque allocation: 1
// - entre 513 pages et 1022 pages, le malloc fonctionne mais l'overhead est trop important: 2
// - entre 313 pages et 512 pages, le malloc fonctionne mais l'overhead est très important: 3
// - entre 273 pages et 312 pages, le malloc fonctionne mais l'overhead est important: 4
// - entre 255 et 272 pages, le malloc fonctionne et l'overhead est raisonnable: 5