#include <stdlib.h>
#include "malloc.h"

int      main()
{
   int   i;
   char  *addr;
   malloc(1024);

   show_alloc_mem();

   i = 0;
   while (i < 1024)
   {
      i++;
   }
   return (0);
}