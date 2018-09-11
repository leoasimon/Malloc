/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 11:52:59 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/11 13:47:39 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

// return the optimal size for a new m_mmap allocation, chunk_size should be SMALL, SMALL or LARGE
static size_t	get_optimal_size(size_t chunk_size)
{
	int initial;
	
	initial = chunk_size * NB_CHUNKS + sizeof(t_malloc) * NB_CHUNKS + sizeof(t_m_mmap);
	return initial + initial % PAGE_SIZE;
}

t_malloc			*init_malloc(t_malloc	*prev, int chunk_size)
{
	t_malloc	*m_malloc;

	printf("size + struct size: %lu\n", chunk_size + sizeof(t_malloc));
	m_malloc = prev + (chunk_size + sizeof(t_malloc));
	m_malloc->is_free = 1;
	m_malloc->next = NULL;
	return m_malloc;
}

t_large_mmap		*init_large_mmap(size_t req_size)
{
	t_large_mmap	*mem_ptr;
	
	mem_ptr = (t_large_mmap *)mmap(NULL, req_size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	mem_ptr->next = NULL;
	return (mem_ptr);
}

// chunk_size should be SMALL, SMALL or LARGE
t_m_mmap			*init_m_mmap(int chunk_size)
{
	t_m_mmap	*m_mmap;

	m_mmap = (t_m_mmap *)mmap(NULL, get_optimal_size(chunk_size), PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	m_mmap->head = init_malloc((t_malloc *)m_mmap, chunk_size);
	m_mmap->next = NULL;
	return m_mmap;
}

t_manager		*init_manager(void)
{
	t_manager *manager;

	manager = (t_manager *)mmap(NULL, sizeof(t_manager), PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	manager->tiny = NULL;
	manager->small = NULL;
	return manager;
}