#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define M (1024 * 1024)

void print(char *s)
{
   write(1, s, strlen(s));
}

int     main()
{
   char *addr1;
   char *addr3;

   addr1 = (char*)malloc(16*M);
   strcpy(addr1, "Bonjours\n");
   print(addr1);
   addr3 = (char*)realloc(addr1, 128*M);
    // addr3 = (char*)malloc(128 * M);
   addr3[127*M] = 42;
   print(addr3);
   free(addr3);
   free(addr1);
   return (0);
}
// $&gt; gcc -o test3 test3.c
// $&gt; ./run.sh ./test3
// Bonjours
// Bonjours
// $&gt;

// Ca fonctionne comme dans l'exemple ?