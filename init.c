/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 11:52:59 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/18 10:51:45 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t		get_optimal_size(size_t chunk_size)
{
	int initial;

	initial = chunk_size * NB_CHUNKS;
	initial += MALLOC_STRUCT_SIZE * NB_CHUNKS + STOCK_STRUCT_SIZE;
	return (initial + initial % PAGE_SIZE);
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

t_malloc			*init_large_mmap(size_t req_size)
{
	t_malloc	*mem_ptr;

	if ((mem_ptr = (t_malloc *)\
		mmap(NULL, req_size, PROT_READ | PROT_WRITE,\
		MAP_ANON | MAP_PRIVATE, -1, 0)))
	{
		mem_ptr->next = NULL;
		mem_ptr->is_free = 0;
		mem_ptr->ret_ptr = mem_ptr + 1;
		mem_ptr->len = req_size;
	}
	return (mem_ptr);
}

t_stock				*init_stock(int chunk_size)
{
	t_stock		*stock;
	size_t		optimal_size;

	optimal_size = get_optimal_size(chunk_size);
	if ((stock = (t_stock *)\
		mmap(NULL, optimal_size, PROT_READ | PROT_WRITE,\
		MAP_ANON | MAP_PRIVATE, -1, 0)))
	{
		stock->head = NULL;
		stock->next = NULL;
		stock->free_bits = optimal_size - STOCK_STRUCT_SIZE;
		stock->len = optimal_size;
	}

	return (stock);
}

t_manager			*init_manager(void)
{
	t_manager *manager;

	if ((manager = (t_manager *)\
		mmap(NULL, sizeof(t_manager), PROT_READ | PROT_WRITE,\
		MAP_ANON | MAP_PRIVATE, -1, 0)))
	{
		manager->tiny = NULL;
		manager->small = NULL;
	}
	return (manager);
}
