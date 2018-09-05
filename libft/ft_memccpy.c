/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:58:20 by lsimon            #+#    #+#             */
/*   Updated: 2016/11/04 16:40:51 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src,
		int c, size_t n)
{
	unsigned int	i;
	char			*dst_c;
	const char		*src_c;

	dst_c = dst;
	src_c = src;
	i = 0;
	while (i < n)
	{
		dst_c[i] = src_c[i];
		if (src_c[i] == c)
			return (&dst[i + 1]);
		i++;
	}
	return (NULL);
}
