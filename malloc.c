/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 10:39:23 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/22 12:49:11 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_manager			g_manager;

t_stock				*get_linked(t_stock *curr, size_t chunk_size,\
							unsigned char *err)
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

t_malloc			*add_large_node(t_malloc *curr,\
					size_t req_size, unsigned char *err)
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

t_malloc			*get_updated_head(t_malloc *curr,\
					size_t req_size, void *pot_addr)
{
	if (!curr)
		return (init_malloc(pot_addr, req_size));
	if (curr->is_free && curr->len >= req_size)
		return (curr);
	curr->next = get_updated_head(curr->next,\
	req_size, curr->ret_ptr + req_size);
	return (curr);
}

t_stock				*retrieve_available_mmap(t_stock *curr, size_t req_size)
{
	if (curr->free_bits >= req_size + sizeof(t_malloc))
		return (curr);
	return (retrieve_available_mmap(curr->next, req_size));
}

void				*malloc(size_t size)
{
	unsigned char	err;

	err = 0;
	if (size <= TINY)
	{
		g_manager.tiny = get_linked(g_manager.tiny, TINY, &err);
		if (err)
			return (NULL);
		return (ret_c(retrieve_available_mmap(g_manager.tiny, size), size));
	}
	if (size <= SMALL)
	{
		g_manager.small = get_linked(g_manager.small, SMALL, &err);
		if (err)
			return (NULL);
		return (ret_c(retrieve_available_mmap(g_manager.small, size), size));
	}
	if (size > SMALL)
	{
		g_manager.large = add_large_node(g_manager.large, size, &err);
		if (err)
			return (NULL);
		return (retrieve_large_tail(g_manager.large));
	}
	return (NULL);
}
