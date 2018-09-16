/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 11:52:59 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/15 17:17:05 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// return the optimal size for a new stock allocation, chunk_size should be TINY, SMALL or LARGE
static size_t	get_optimal_size(size_t chunk_size)
{
	int initial;
	
	initial = chunk_size * NB_CHUNKS + MALLOC_STRUCT_SIZE * NB_CHUNKS + STOCK_STRUCT_SIZE;
	return initial + initial % PAGE_SIZE;
}

t_malloc			*init_malloc(void *addr, size_t req_size)
{
	t_malloc	*m_malloc;

	m_malloc = (t_malloc *)addr;
	m_malloc->is_free = 0;
	m_malloc->len = req_size;
	m_malloc->next = NULL;
	m_malloc->ret_ptr = m_malloc + MALLOC_STRUCT_SIZE;
	return m_malloc;
}

t_malloc		*init_large_mmap(size_t req_size)
{
	t_malloc	*mem_ptr;
	
	mem_ptr = (t_malloc *)mmap(NULL, req_size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	mem_ptr->next = NULL;
	mem_ptr->is_free = 0;
	mem_ptr->ret_ptr = mem_ptr + MALLOC_STRUCT_SIZE;
	mem_ptr->len = req_size;
	return (mem_ptr);
}

// chunk_size should be SMALL, SMALL or LARGE
t_stock			*init_stock(int chunk_size)
{
	t_stock		*stock;
	size_t		optimal_size;

	optimal_size = get_optimal_size(chunk_size);
	stock = (t_stock *)mmap(NULL, optimal_size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	stock->head = NULL;
	stock->next = NULL;
	stock->free_bits = optimal_size - STOCK_STRUCT_SIZE; //TODO: Fix this?
	stock->len = optimal_size;

	printf("Fresh stock: start: %p, len: %zu, end: %p\n\n", stock, stock->len, (void *)stock + stock->len);
	return (stock);
}

t_manager		*init_manager(void)
{
	t_manager *manager;

	manager = (t_manager *)mmap(NULL, sizeof(t_manager), PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	manager->tiny = NULL;
	manager->small = NULL;
	return manager;
}