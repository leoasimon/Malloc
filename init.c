/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 11:52:59 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/23 11:38:04 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_manager	g_manager;

static size_t		get_optimal_size(size_t chunk_size)
{
	size_t initial;

	initial = (size_t)chunk_size * NB_CHUNKS;
	initial += sizeof(t_block) * NB_CHUNKS + sizeof(t_zone);
	return ((size_t)(initial / getpagesize()) + 1) * getpagesize();
}

t_block			*init_block(void *addr, size_t req_size)
{
	t_block	*m_block;

	m_block = (t_block *)addr;
	m_block->is_free = 0;
	m_block->len = req_size;
	m_block->next = NULL;
	m_block->ret_ptr = m_block + 1;
	return (m_block);
}

t_zone				*init_zone(size_t sizetype)
{
	t_zone		*zone;
	size_t		optimal_size;

	optimal_size = get_optimal_size(sizetype);
	if ((zone = (t_zone *)\
		mmap(NULL, optimal_size, PROT_READ | PROT_WRITE,\
		MAP_ANON | MAP_PRIVATE, -1, 0)))
	{
		zone->head = NULL;
		zone->next = NULL;
		zone->free_bytes = optimal_size - sizeof(t_zone);
		zone->len = optimal_size;
	}
	return (zone);
}
