/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:44:21 by lsimon            #+#    #+#             */
/*   Updated: 2016/11/04 11:52:09 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if ((mem = (void *)malloc(size)))
	{
		ft_memset(mem, 0, size);
		return (mem);
	}
	return (NULL);
}
