/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 09:43:28 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/22 14:38:33 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_malloc		*find_ptr_in_mallocs(void *ptr, t_malloc *curr, int *err)
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
	return (find_ptr_in_mallocs(ptr, curr->next, err));
}

static t_stock		*in_list(void *ptr, t_stock *curr)
{
	if (!curr)
		return (NULL);
	if (ptr > (void *)curr && ptr <= (void *)curr + curr->len)
		return (curr);
	return (in_list(ptr, curr->next));
}

static t_malloc		*locate_ptr(void *ptr, int *err)
{
	t_malloc	*found_malloc;
	t_stock		*list;

	found_malloc = NULL;
	list = NULL;
	if (g_manager.tiny && (list = in_list(ptr, g_manager.tiny)))
		return (find_ptr_in_mallocs(ptr, list->head, err));
	else if (g_manager.small && (list = in_list(ptr, g_manager.small)))
		return (find_ptr_in_mallocs(ptr, list->head, err));
	else if (g_manager.large && !found_malloc)
		return (find_ptr_in_mallocs(ptr, g_manager.large, err));
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
	t_malloc		*found_malloc;
	void			*new_malloc;
	int				err;

	new_malloc = NULL;
	err = 0;
	found_malloc = locate_ptr(ptr, &err);
	if (found_malloc)
	{
		if (!size)
			return (handle_no_size(ptr));
		if (size <= found_malloc->len)
		{
			found_malloc->len = size;
			return (found_malloc->ret_ptr);
		}
		if (!(new_malloc = malloc(size)))
			return (NULL);
		ft_memcpy(new_malloc, ptr, found_malloc->len);
		found_malloc->is_free = 1;
		return (new_malloc);
	}
	return (err > 0 ? NULL : malloc(size));
}
