/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 10:39:23 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/23 11:38:04 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_manager	g_manager;

/*
Return zone with enough free bytes,
or allocate a new zone if not
*/
static t_zone		*get_zones(t_zone *curr, size_t st, int *err)
{
	t_zone	*new;

	if (!curr)
	{
		new = init_zone(st);
		*err = new ? *err : *err + 1;
		return (new);
	}
	if (curr->free_bytes < (size_t)st + sizeof(t_block))
		curr->next = get_zones(curr->next, st, err);
	return (curr);
}

void				*malloc_small(size_t req_size)
{
	int	err;

	err = 0;
	if (req_size <= TINY)
	{
		g_manager.tiny = get_zones(g_manager.tiny, TINY, &err);
		return (err ? NULL : \
		retrieve_chunk(get_usable_zone(g_manager.tiny, req_size),\
		req_size));
	}
	if (req_size <= SMALL)
	{
		g_manager.small = get_zones(g_manager.small, SMALL, &err);
		return (err ? NULL : \
		retrieve_chunk(get_usable_zone(g_manager.small, req_size),\
		req_size));
	}
	return (NULL);
}

void				*malloc(size_t req_size)
{
	int	err;

	err = 0;
	if (req_size <= SMALL)
		return (malloc_small(req_size));
	g_manager.large = add_large_node(g_manager.large, req_size, &err);
	return (err ? NULL : retrieve_large_tail(g_manager.large));
}
