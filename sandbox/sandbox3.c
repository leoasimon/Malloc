/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 13:37:02 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/17 09:09:56 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../malloc.h"

int	main(void)
{
	void	*ptr, *ptr2, *ptr3;
	int		i;

	i = 0;
	ptr = malloc(SMALL);
	ptr2 = malloc(SMALL);
	ptr3 = malloc(SMALL);
	show_alloc_mem();
	free(ptr);
	show_alloc_mem();
	free(ptr2);
	show_alloc_mem();
}