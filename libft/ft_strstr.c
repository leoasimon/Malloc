/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 09:23:35 by lsimon            #+#    #+#             */
/*   Updated: 2016/11/09 12:02:15 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int		i;
	int		j;
	char	*big_c;
	int		start;

	start = 0;
	big_c = (char *)big;
	if (ft_strcmp(little, "") == 0)
		return (big_c);
	while (big[start])
	{
		i = start;
		j = 0;
		while (big[i++] == little[j++])
			if (!little[j])
				return (&big_c[start]);
		start++;
	}
	return (NULL);
}
