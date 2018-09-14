/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 12:30:43 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/14 15:10:51 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "malloc.h"

int	main(void)
{
	void	*alloc;

	for (int i = 0; i < 5; i++) {
		alloc = malloc(TINY);
	}
	for (int i = 0; i < 5; i++) {
		alloc = malloc(SMALL);
	}
	for (int i = 0; i < 5; i++) {
		alloc = malloc(SMALL * 2);
	}

	ft_putstr("\n\n-- libft works.\n\n");
	show_alloc_mem();

	free(alloc);
	show_alloc_mem();

	return (0);
}
