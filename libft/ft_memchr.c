/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 11:32:20 by lsimon            #+#    #+#             */
/*   Updated: 2016/11/09 11:44:05 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*sc;
	unsigned char	cc;

	sc = (unsigned char*)s;
	cc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (sc[i] == cc)
			return (&sc[i]);
		i++;
	}
	return (NULL);
}
