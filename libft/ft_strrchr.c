/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 18:39:04 by lsimon            #+#    #+#             */
/*   Updated: 2016/11/07 11:11:30 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		current;
	char	*s_c;

	current = -1;
	i = 0;
	s_c = (char *)s;
	while (s[i])
	{
		if (s[i] == c)
			current = i;
		i++;
	}
	if (s[i] == c)
		current = i;
	if (current > -1)
		return (&s_c[current]);
	return (NULL);
}
