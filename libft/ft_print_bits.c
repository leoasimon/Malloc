/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 09:19:16 by lsimon            #+#    #+#             */
/*   Updated: 2016/11/11 09:19:22 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_bits(unsigned char octet)
{
	int		nb;
	char	bit;

	nb = 128;
	while (nb > 0)
	{
		bit = octet / nb + '0';
		write(1, &bit, 1);
		octet %= nb;
		nb /= 2;
	}
}
