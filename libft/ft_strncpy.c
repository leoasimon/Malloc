/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 16:18:22 by lsimon            #+#    #+#             */
/*   Updated: 2016/11/07 19:01:32 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	unsigned int i;

	i = 0;
	while (i < len)
	{
		if (src[i] == '\0')
		{
			while (i < len)
				dest[i++] = '\0';
			return (dest);
		}
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
