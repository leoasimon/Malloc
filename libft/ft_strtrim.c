/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 08:35:28 by lsimon            #+#    #+#             */
/*   Updated: 2016/11/09 11:23:36 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	strtrimlen(char const *s)
{
	int i;
	int start;
	int end;

	i = 0;
	start = -1;
	end = -1;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
			i++;
		while (s[i] && (s[i] != ' ' && s[i] != '\t' && s[i] != '\n'))
		{
			if (start < 0)
				start = i;
			i++;
			end = i;
		}
	}
	if (end < 0)
		end = i;
	return (end - start);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	len = strtrimlen(s);
	if (!(new = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
	while (j < len)
		new[j++] = s[i++];
	new[j] = '\0';
	return (new);
}
