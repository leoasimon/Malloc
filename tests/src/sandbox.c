/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 12:30:43 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/14 12:42:31 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "../../malloc.h"

int	main(void)
{
	void	*alloc;

	for (int i = 0; i < 5; i++) {
		alloc = ft_malloc(TINY);
	}
	for (int i = 0; i < 5; i++) {
		alloc = ft_malloc(SMALL);
	}
	for (int i = 0; i < 5; i++) {
		alloc = ft_malloc(SMALL * 2);
	}

	ft_putstr("\n\n-- libft works.\n\n");
	show_alloc_mem();

	return (0);
}
