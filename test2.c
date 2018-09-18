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
      free(addr);
      i++;
   }
   return (0);
}
// $&gt; gcc -o test2 test2.c

// Nous allons comparer le nombre de "page reclaims" à celui de test0
// est1. S'il y a autant de "page reclaims" ou plus que test1, le free
// arche pas.

// $&gt;./run.sh /usr/bin/time -l ./test2

// Le free fonctionne-t-il ? (moins de "pages reclaims" que test1)

// test2 a maximum 3 "page reclaims" en plus que test0 ?