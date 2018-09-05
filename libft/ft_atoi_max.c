/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_max.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 15:29:42 by lsimon            #+#    #+#             */
/*   Updated: 2016/12/22 15:36:33 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi_max(const char *str, int max)
{
	int	i;
	int	is_neg;
	int	result;

	is_neg = 0;
	i = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		is_neg++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] > 47 && str[i] < 58)
	{
		result *= 10;
		result += (str[i] - '0');
		i++;
		if (result >= max)
			return (is_neg ? -max : max);
	}
	return (is_neg ? -result : result);
}
