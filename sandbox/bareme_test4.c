#include "../malloc.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void print(char *s)
{
	write(1, s, strlen(s));
}

int    main()
{
	char *addr;

	addr = malloc(16);
	free(NULL);
	free((void *)addr + 5);
	if (realloc((void *)addr + 5, 10) == NULL)
		print("Bonjours\n");
}

// <br>$&gt; gcc -o test4 test4.c
// <br>$&gt; ./run/sh ./test4
// <br>Bonjours
// <br>
// <br>En cas d'erreur, realloc doit renvoyer NULL. Est-ce que le "Bonjours" est affiché comme dans l'exemple ?
// <br>Si le programme réagit de façon malsaine (segfault ou autres), la
// soutenance s'arrête et vous devez sélectionner Crash en haut du barême.