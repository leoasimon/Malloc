/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:15:44 by lsimon            #+#    #+#             */
/*   Updated: 2016/11/07 11:26:50 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	return_value;

	i = 0;
	j = 0;
	if (size < 1)
		return (ft_strlen(src));
	while (dst[i])
		i++;
	if (i > size - 1)
		return (ft_strlen(src) + size);
	return_value = ft_strlen(src) + ft_strlen(dst);
	while (src[j] && i < (size - 1))
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (return_value);
}
