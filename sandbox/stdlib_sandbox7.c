#include "../malloc.h"

void print(char *s)
{
	write(1, s, strlen(s));
}

int    main()
{
	char *addr;

	print("With ft_libft_malloc: Error case\n");
	addr = malloc(16);
	free(NULL);
	free((void *)addr + 5);
	if (realloc((void *)addr + 5, 10) == NULL)
	print("Bonjours\n");
}