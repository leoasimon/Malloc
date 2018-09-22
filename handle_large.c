/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_large.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 13:25:18 by ekelen            #+#    #+#             */
/*   Updated: 2018/09/22 14:33:31 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_malloc		*init_large_mmap(size_t req_size)
{
	t_malloc		*mem_ptr;
	int				pagesize;
	size_t			optimal_size;

	pagesize = (size_t)getpagesize();
	optimal_size = (((req_size + sizeof(t_malloc)) / pagesize) + 1) * pagesize;
	if (optimal_size < req_size)
		return (NULL);
	if ((mem_ptr = (t_malloc *)\
		mmap(NULL, optimal_size, PROT_READ | PROT_WRITE,\
		MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	mem_ptr->next = NULL;
	mem_ptr->is_free = 0;
	mem_ptr->ret_ptr = mem_ptr + 1;
	mem_ptr->len = req_size;
	return (mem_ptr);
}

t_malloc			*add_large_node(t_malloc *curr, size_t req_size, int *err)
{
	t_malloc	*new;

	new = NULL;
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
