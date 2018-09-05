/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:04:55 by lsimon            #+#    #+#             */
/*   Updated: 2016/12/16 10:49:07 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*src_c;
	char	*dst_c;
	size_t	i;

	i = 0;
	src_c = (char *)src;
	dst_c = (char *)dst;
	if (src < dst)
	{
		len--;
		while ((int)(len) >= 0)
		{
			dst_c[len] = src_c[len];
			len--;
		}
	}
	else
		ft_strncpy(dst_c, src_c, len);
	return (dst);
}
