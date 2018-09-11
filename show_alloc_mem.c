/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:40:55 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/11 09:44:04 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_malloc.h"

extern t_manager	*manager;

static void print_chunk(t_malloc *last, int i, size_t chunk_size)
{
	int offset;
	t_malloc	*end;
	
	offset = i * sizeof(t_malloc) + (i + 1) * chunk_size;
	end = last + offset;
	printf("%p - %p : %d octets\n", last, end, offset / 8);
}

static void print_malloc_mem(t_malloc *curr, t_malloc *last, int i, size_t chunk_size)
{
	if ((last && !curr) || (last && curr->is_free))
	{
		print_chunk(last, i, chunk_size);
		last = NULL;
	}
	if (!last && curr && curr->is_free)
		last = curr;
	if (curr)
		print_malloc_mem(curr->next, last, i + 1, chunk_size);
}

static void show_mem(t_m_mmap *m_mmap, char *title, size_t chunk_size)
{
	printf("%s: %p\n", title, m_mmap);
	print_malloc_mem(m_mmap->head, NULL, 0, chunk_size);
}

void	show_alloc_mem(void)
{
	if (manager->small) show_mem(manager->small, "SMALL", SMALL);
	if (manager->tiny) show_mem(manager->tiny, "tiny", TINY);
}