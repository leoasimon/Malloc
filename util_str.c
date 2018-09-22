/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 14:26:48 by ekelen            #+#    #+#             */
/*   Updated: 2018/09/22 14:31:33 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	print_hex(int value)
{
	char const *base = "0123456789abcdef";

	if (value / 16 > 1)
		print_hex(value / 16);
	write(1, base + value % 16, 1);
}

void		ft_print_addr(void *addr)
{
	if (addr)
	{
		ft_putstr("0x10");
		print_hex((int)addr);
	}
}

void		ft_print_unsigned_long(size_t n)
{
	const unsigned char rem = n % 10;

	if (n >= 10)
		ft_print_unsigned_long(n / 10);
	ft_putchar(rem + 48);
}

void		ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}
