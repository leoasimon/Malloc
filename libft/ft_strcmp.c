/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 16:19:11 by lsimon            #+#    #+#             */
/*   Updated: 2016/11/07 17:19:52 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*sc1;
	unsigned char	*sc2;

	sc1 = (unsigned char *)s1;
	sc2 = (unsigned char *)s2;
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (sc1[i] - sc2[i]);
		i++;
	}
	return (0);
}
