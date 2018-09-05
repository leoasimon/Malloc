/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_count_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 12:46:28 by lsimon            #+#    #+#             */
/*   Updated: 2016/12/08 09:21:20 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_word_count_line(const char *s)
{
	int	i;
	int count;

	count = 0;
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (s[i] && s[i] != '\n')
			count++;
		while (s[i] && s[i] != ' ' && s[i] != '\n')
			i++;
	}
	return (count);
}
