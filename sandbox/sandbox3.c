/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 13:37:02 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/17 11:57:36 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../malloc.h"
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	// void	*ptr, *ptr2, *ptr3;
	char *s;
	int		i;

	i = 0;
	// ptr = malloc(SMALL);
	// ptr2 = malloc(SMALL);
	// ptr3 = malloc(SMALL);
	// show_alloc_mem();
	// free(ptr);
	// show_alloc_mem();
	// free(ptr2);
	// show_alloc_mem();

	// ptr = malloc(TINY);
	// ptr2 = malloc(SMALL);
	// ptr3 = malloc(SMALL + 10);
	// show_alloc_mem();
	// free(ptr);
	// show_alloc_mem();
	// free(ptr2);
	// show_alloc_mem();
	// free(ptr3);
	// show_alloc_mem();
	s = (char *)malloc(100);
	s = "hellooooooooooooooooo";
	s = realloc((char *)s + 5, 10);
	// if (s == NULL)
	// 	printf("Bonjours\n");
	printf("%s\n", s);
	return (0);
}