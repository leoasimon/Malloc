/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 13:51:11 by ekelen            #+#    #+#             */
/*   Updated: 2018/09/23 11:38:04 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block		*get_updated_head(t_block *curr, size_t rsz, void *addr)
{
	if (!curr)
		return (init_block(addr, rsz));
	if (curr->is_free && curr->len >= rsz)
		return (curr);
	curr->next = get_updated_head(curr->next,\
	rsz, curr->ret_ptr + rsz);
	return (curr);
}

static void		*get_ret_ptr(t_block *curr, size_t s, size_t *free_bytes)
{
	if (curr->is_free && curr->len >= s)
	{
		curr->is_free = 0;
		return (curr->ret_ptr);
	}
	if (curr->next)
		return (get_ret_ptr(curr->next, s, free_bytes));
	*free_bytes -= curr->len + sizeof(t_block);
	return (curr->ret_ptr);
}

void			*retrieve_chunk(t_zone *zone, size_t req_size)
{
	zone->head = get_updated_head(zone->head, req_size,\
	(void *)zone + sizeof(t_zone));
	return (get_ret_ptr(zone->head, req_size, &(zone->free_bytes)));
}

t_zone			*get_usable_zone(t_zone *curr, size_t req_size)
{
	if (curr->free_bytes >= req_size + sizeof(t_block))
		return (curr);
	return (get_usable_zone(curr->next, req_size));
}
