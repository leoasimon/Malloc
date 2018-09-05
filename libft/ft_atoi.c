/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 08:05:57 by lsimon            #+#    #+#             */
/*   Updated: 2016/12/03 15:19:43 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
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
	}
	if (is_neg)
		return (result * -1);
	return (result);
}
