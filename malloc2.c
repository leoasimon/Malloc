/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 12:39:52 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/22 12:49:15 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*retrieve_large_tail(t_malloc *curr)
{
	if (!curr->next)
		return (curr->ret_ptr);
	return (retrieve_large_tail(curr->next));
}

void	*get_ret_ptr(t_malloc *curr, size_t s, size_t *free_bits)
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

void	*ret_c(t_stock *stock, size_t req_size)
{
	stock->head = get_updated_head(stock->head, req_size,\
	(void *)stock + sizeof(t_stock));
	return (get_ret_ptr(stock->head, req_size, &(stock->free_bits)));
}
