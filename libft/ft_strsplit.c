/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:58:57 by lsimon            #+#    #+#             */
/*   Updated: 2016/11/09 14:51:46 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		array_len(const char *s, char c)
{
	int	i;
	int count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int		str_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char		**fill(char **array, char const *s, char c)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			k = 0;
			if (!(array[j] = (char*)malloc(sizeof(char) * str_len(&s[i], c))))
				return (NULL);
			while (s[i] && s[i] != c)
				array[j][k++] = s[i++];
			array[j++][k] = '\0';
		}
	}
	array[j] = NULL;
	return (array);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	if (!(array = (char**)malloc(sizeof(char*) * (array_len(s, c) + 1))))
		return (NULL);
	if (!(array = fill(array, s, c)))
		return (NULL);
	return (array);
}
