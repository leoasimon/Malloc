/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 09:30:01 by lsimon            #+#    #+#             */
/*   Updated: 2016/11/08 07:49:02 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	itoalen(int n)
{
	int	i;

	i = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	mult(int nb)
{
	int i;
	int result;

	i = 1;
	result = 1;
	while (i < nb)
	{
		i++;
		result *= 10;
	}
	return (result);
}

static void	min_int(int *i, int *n, char *s)
{
	if (*n == -2147483648)
	{
		s[*i] = '-';
		s[*i + 1] = '2';
		*n = 147483648;
		*i += 2;
	}
}

char		*ft_itoa(int n)
{
	char		*s;
	int			i;
	int			len;

	i = 0;
	len = itoalen(n);
	if (!(s = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	min_int(&i, &n, s);
	if (n < 0)
	{
		s[i++] = '-';
		n *= -1;
	}
	while (i < len)
	{
		s[i] = (n / (mult(len - i)) + '0');
		n %= (mult(len - i));
		i++;
	}
	s[i] = '\0';
	return (s);
}
