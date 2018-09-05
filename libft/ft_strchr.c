/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 18:02:16 by lsimon            #+#    #+#             */
/*   Updated: 2016/11/07 11:05:20 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*s_c;

	i = 0;
	s_c = (char *)s;
	while (s[i])
	{
		if (s[i] == c)
			return (&s_c[i]);
		i++;
	}
	if (s[i] == c)
		return (&s_c[i]);
	return (NULL);
}
