/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 13:51:11 by ekelen            #+#    #+#             */
/*   Updated: 2018/09/22 14:38:14 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc		*get_updated_head(t_malloc *curr, size_t rsz, void *addr)
{
	if (!curr)
		return (init_malloc(addr, rsz));
	if (curr->is_free && curr->len >= rsz)
		return (curr);
	curr->next = get_updated_head(curr->next,\
	rsz, curr->ret_ptr + rsz);
	return (curr);
}

static void		*get_ret_ptr(t_malloc *curr, size_t s, size_t *free_bits)
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

void			*retrieve_chunk(t_stock *stock, size_t req_size)
{
	stock->head = get_updated_head(stock->head, req_size,\
	(void *)stock + sizeof(t_stock));
	return (get_ret_ptr(stock->head, req_size, &(stock->free_bits)));
}

t_stock			*get_usable_stock(t_stock *curr, size_t req_size)
{
	if (curr->free_bits >= req_size + sizeof(t_malloc))
		return (curr);
	return (get_usable_stock(curr->next, req_size));
}
