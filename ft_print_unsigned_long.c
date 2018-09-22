/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_long.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 10:51:27 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/22 12:30:04 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	ft_print_unsigned_long(size_t n)
{
	const unsigned char rem = n % 10;

	if (n >= 10)
		ft_print_unsigned_long(n / 10);
	ft_putchar(rem + 48);
}
