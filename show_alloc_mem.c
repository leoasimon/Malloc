/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 11:31:30 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/17 11:31:43 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_manager	*manager;

static void	print_mallocs(t_malloc	*curr, int *total)
{
	if (curr)
	{
		if (!curr->is_free)
		{
			ft_print_addr(curr->ret_ptr);
			ft_putstr(" - ");
			ft_print_addr(curr->ret_ptr + curr->len);
			ft_putstr(" : ");
			ft_putnbr(curr->len);
			ft_putstr(" octets\n");
			*total += curr->len;
		}
		print_mallocs(curr->next, total);
	}
}

static void	print_heap(t_stock *heap, char *title, int *total)
{
	if (heap)
	{
		ft_putstr(title);
		ft_putstr(" : ");
		ft_print_addr(heap);
		ft_putchar('\n');
		print_mallocs(heap->head, total);
		print_heap(heap->next, title, total);
	}
}

static void	print_large_heap(t_malloc *heap, int *total)
{
	if (heap)
	{
		ft_putstr("LARGE : ");
		ft_print_addr(heap);
		ft_putchar('\n');
		ft_print_addr(heap->ret_ptr);
		ft_putstr(" - ");
		ft_print_addr(heap->ret_ptr + heap->len);
		ft_putstr(" : ");
		ft_putnbr(heap->len);
		ft_putstr(" octets\n");
		*total += heap->len;
		print_large_heap(heap->next, total);
	}
}

void		show_alloc_mem(void)
{
	int	total;

	total = 0;
	if (manager)
	{
		print_heap(manager->tiny, "TINY", &total);
		print_heap(manager->small, "SMALL", &total);
		print_large_heap(manager->large, &total);
		ft_putstr("TOTAL: ");
		ft_putnbr(total);
		ft_putstr(" octets\n");
	}
}
