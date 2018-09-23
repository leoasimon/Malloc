/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 11:52:59 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/23 08:58:45 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_manager	g_manager;

static size_t		get_optimal_size(t_stype chunk_size)
{
	size_t initial;

	initial = (size_t)chunk_size * NB_CHUNKS;
	initial += sizeof(t_malloc) * NB_CHUNKS + sizeof(t_stock);
	return ((size_t)(initial / getpagesize()) + 1) * getpagesize();
}

t_malloc			*init_malloc(void *addr, size_t req_size)
{
	t_malloc	*m_malloc;

	m_malloc = (t_malloc *)addr;
	m_malloc->is_free = 0;
	m_malloc->len = req_size;
	m_malloc->next = NULL;
	m_malloc->ret_ptr = m_malloc + 1;
	return (m_malloc);
}

t_stock				*init_stock(size_t sizetype)
{
	t_stock		*stock;
	size_t		optimal_size;

	optimal_size = get_optimal_size(sizetype);
	if ((stock = (t_stock *)\
		mmap(NULL, optimal_size, PROT_READ | PROT_WRITE,\
		MAP_ANON | MAP_PRIVATE, -1, 0)))
	{
		stock->head = NULL;
		stock->next = NULL;
		stock->free_bits = optimal_size - sizeof(t_stock);
		stock->len = optimal_size;
	}
	return (stock);
}
