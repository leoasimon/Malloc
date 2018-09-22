/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 10:04:50 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/22 12:29:42 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_hex(int value)
{
	char const *base = "0123456789abcdef";

	if (value / 16 > 1)
		print_hex(value / 16);
	write(1, base + value % 16, 1);
}

void	ft_print_addr(void *addr)
{
	if (addr)
	{
		ft_putstr("0x10");
		print_hex((int)addr);
	}
}
