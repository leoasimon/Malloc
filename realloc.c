/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 09:43:28 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/23 11:38:04 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block		*find_ptr_in_blocks(void *ptr, t_block *curr, int *err)
{
	if (!curr)
		return (NULL);
	if (ptr == (void *)curr->ret_ptr && !curr->is_free)
		return (curr);
	else if (ptr >= (void *)curr && ptr < (void *)curr->ret_ptr + curr->len)
	{
		*err = 1;
		return (NULL);
	}
	return (find_ptr_in_blocks(ptr, curr->next, err));
}

static t_zone		*in_list(void *ptr, t_zone *curr)
{
	if (!curr)
		return (NULL);
	if (ptr > (void *)curr && ptr <= (void *)curr + curr->len)
		return (curr);
	return (in_list(ptr, curr->next));
}

static t_block		*locate_ptr(void *ptr, int *err)
{
	t_block	*found_block;
	t_zone		*list;

	found_block = NULL;
	list = NULL;
	if (g_manager.tiny && (list = in_list(ptr, g_manager.tiny)))
		return (find_ptr_in_blocks(ptr, list->head, err));
	else if (g_manager.small && (list = in_list(ptr, g_manager.small)))
		return (find_ptr_in_blocks(ptr, list->head, err));
	else if (g_manager.large && !found_block)
		return (find_ptr_in_blocks(ptr, g_manager.large, err));
	else
		return (NULL);
}

void				*handle_no_size(void *ptr)
{
	free(ptr);
	return (NULL);
}

void				*realloc(void *ptr, size_t size)
{
	t_block		*found_block;
	void			*new_block;
	int				err;

	new_block = NULL;
	err = 0;
	found_block = locate_ptr(ptr, &err);
	if (found_block)
	{
		if (!size)
			return (handle_no_size(ptr));
		if (size <= found_block->len)
		{
			found_block->len = size;
			return (found_block->ret_ptr);
		}
		if (!(new_block = malloc(size)))
			return (NULL);
		ft_memcpy(new_block, ptr, found_block->len);
		found_block->is_free = 1;
		return (new_block);
	}
	return (err > 0 ? NULL : malloc(size));
}
