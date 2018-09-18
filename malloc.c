/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 10:39:23 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/18 11:00:43 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_manager	*manager = NULL;

t_stock		*get_linked(t_stock *curr, size_t chunk_size)
{
	if (!curr)
		return (init_stock(chunk_size));
	if (curr->free_bits < chunk_size + MALLOC_STRUCT_SIZE)
		curr->next = get_linked(curr->next, chunk_size);
	return (curr);
}

t_malloc	*add_large_node(t_malloc *curr, size_t req_size)
{
	if (!curr)
		return (init_large_mmap(req_size));
	curr->next = add_large_node(curr->next, req_size);
	return (curr);
}

void		*retrieve_large_tail(t_malloc *curr)
{
	if (!curr->next)
		return (curr->ret_ptr);
	return (retrieve_large_tail(curr->next));
}

t_malloc	*get_updated_head(t_malloc *curr, size_t req_size, void *pot_addr)
{
	if (!curr)
		return (init_malloc(pot_addr, req_size));
	curr->next = get_updated_head(curr->next,\
	req_size, curr->ret_ptr + req_size);
	return (curr);
}

void	*get_ret_ptr(t_malloc *curr)
{
	if (curr->next)
		return (get_ret_ptr(curr->next));
	return (curr->ret_ptr);
}

void	*retrieve_chunk(t_stock *stock, size_t req_size)
{
	stock->head = get_updated_head(stock->head, req_size,\
	(void *)stock + STOCK_STRUCT_SIZE);
	stock->free_bits -= req_size + MALLOC_STRUCT_SIZE;
	return (get_ret_ptr(stock->head));
}

t_stock	*retrieve_available_mmap(t_stock *curr, size_t req_size)
{
	if (curr->free_bits >= req_size + MALLOC_STRUCT_SIZE)
		return (curr);
	return (retrieve_available_mmap(curr->next, req_size));
}

void	*malloc(size_t req_size)
{
	static int		debug_count = 0;

	debug_count++;
	if (manager == NULL)
		manager = init_manager();
	if (req_size <= TINY)
	{
		manager->tiny = get_linked(manager->tiny, TINY);
		return (\
		retrieve_chunk(retrieve_available_mmap(manager->tiny, req_size),\
		req_size));
	}
	if (req_size <= SMALL)
	{
		manager->small = get_linked(manager->small, SMALL);
		return (\
		retrieve_chunk(retrieve_available_mmap(manager->small, req_size),\
		req_size));
	}
	if (req_size > SMALL)
	{
		manager->large = add_large_node(manager->large, req_size);
		return (retrieve_large_tail(manager->large));
	}
	return (NULL);
}
