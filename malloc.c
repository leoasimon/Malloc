/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 10:39:23 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/22 11:22:34 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_manager	g_manager;

t_stock				*get_linked(t_stock *curr, size_t chunk_size, unsigned char *err)
{
	t_stock	*new;

	if (!curr)
	{
		new = init_stock(chunk_size);
		*err = new ? *err : *err + 1;
		return (new);
	}
	if (curr->free_bits < chunk_size + sizeof(t_malloc))
		curr->next = get_linked(curr->next, chunk_size, err);
	return (curr);
}

t_malloc			*add_large_node(t_malloc *curr, size_t req_size, unsigned char *err)
{
	t_malloc	*new;
	
	if (!curr)
	{
		new = init_large_mmap(req_size);
		*err = new ? *err : *err + 1;
		return (new);
	}
	curr->next = add_large_node(curr->next, req_size, err);
	return (curr);
}

void				*retrieve_large_tail(t_malloc *curr)
{
	if (!curr->next)
		return (curr->ret_ptr);
	return (retrieve_large_tail(curr->next));
}

t_malloc			*get_updated_head(t_malloc *curr, size_t req_size, void *pot_addr)
{
	if (!curr)
		return (init_malloc(pot_addr, req_size));
	if (curr->is_free && curr->len >= req_size)
		return (curr);
	curr->next = get_updated_head(curr->next,\
	req_size, curr->ret_ptr + req_size);
	return (curr);
}

void				*get_ret_ptr(t_malloc *curr, size_t s, size_t *free_bits)
{
	if (curr->is_free && curr->len >= s)
	{
		curr->is_free = 0;
		return (curr->ret_ptr);
	}
	if (curr->next)
		return (get_ret_ptr(curr->next, s, free_bits));
	*free_bits -= curr->len + sizeof(t_malloc);
	return (curr->ret_ptr);
}

void	*retrieve_chunk(t_stock *stock, size_t req_size)
{
	stock->head = get_updated_head(stock->head, req_size,\
	(void *)stock + sizeof(t_stock));
	return (get_ret_ptr(stock->head, req_size, &(stock->free_bits)));
}

t_stock	*retrieve_available_mmap(t_stock *curr, size_t req_size)
{
	if (curr->free_bits >= req_size + sizeof(t_malloc))
		return (curr);
	return (retrieve_available_mmap(curr->next, req_size));
}

void	*malloc(size_t req_size)
{
	unsigned char	err;

	err = 0;
	if (req_size <= TINY)
	{
		g_manager.tiny = get_linked(g_manager.tiny, TINY, &err);
		if (err)
			return (NULL);
		return (\
		retrieve_chunk(retrieve_available_mmap(g_manager.tiny, req_size),\
		req_size));
	}
	if (req_size <= SMALL)
	{
		g_manager.small = get_linked(g_manager.small, SMALL, &err);
		if (err)
			return (NULL);
		return (\
		retrieve_chunk(retrieve_available_mmap(g_manager.small, req_size),\
		req_size));
	}
	if (req_size > SMALL)
	{
		g_manager.large = add_large_node(g_manager.large, req_size, &err);
		if (err)
			return (NULL);
		return (retrieve_large_tail(g_manager.large));
	}
	return (NULL);
}
