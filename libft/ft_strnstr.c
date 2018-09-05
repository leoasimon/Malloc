/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becorbel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:08:42 by becorbel          #+#    #+#             */
/*   Updated: 2016/11/09 14:59:35 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	c;

	i = 0;
	c = 0;
	if (little[0] == '\0')
		return (char*)(big);
	while (i < len && big[i])
	{
		j = i;
		c = 0;
		while (big[j] == little[c] && j < len)
		{
			j++;
			c++;
			if (little[c] == '\0')
				return (char*)(&big[i]);
		}
		i++;
	}
	return (NULL);
}
