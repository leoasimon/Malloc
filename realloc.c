/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 09:43:28 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/16 14:13:03 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_manager	*manager;

static t_malloc *find_ptr_in_mallocs(void *ptr, t_malloc *curr, int *err)
{
	if (!curr) return NULL;
	
	if (ptr == (void *)curr->ret_ptr && !curr->is_free) return curr;
	else if (
		ptr > (void *)curr->ret_ptr && 
		ptr <= (void *)curr->ret_ptr + curr->len)
		{
			*err = 1;
			return NULL;
		}
	return find_ptr_in_mallocs(ptr, curr->next, err);
}

static t_malloc	*locate_ptr(void *ptr, int *err)
{
	t_malloc *found_malloc;

	found_malloc = NULL;
	if (!manager) return NULL;
	if (manager->tiny) found_malloc = find_ptr_in_mallocs(ptr, manager->tiny->head, err);
	if (manager->small && !found_malloc) found_malloc = find_ptr_in_mallocs(ptr, manager->tiny->head, err);
	if (manager->large && !found_malloc) found_malloc = find_ptr_in_mallocs(ptr, manager->large, err);
	return found_malloc;
}

static void clear_allocated_mem(t_malloc	*ptr)
{
	ptr->is_free = 1;
	ft_bzero(ptr->ret_ptr, ptr->len);
}

static int 	ft_min(int v1, int v2)
{
	return v1 <= v2 ? v1 : v2;
}

void	*realloc(void	*ptr, size_t size)
{
	t_malloc		*found_malloc;
	t_malloc		*new_malloc;
	int			 	err;
	
	new_malloc = NULL;
	err = 0;
	
	found_malloc = locate_ptr(ptr, &err);
	if (found_malloc)
	{
		if (!size)
		{
			free(ptr);
			return NULL;
		}
		if (size <= found_malloc->len) {
			found_malloc->len = size;
			return found_malloc->ret_ptr;
		}
		new_malloc = malloc(ft_min((int)size, (int)found_malloc->len));
		ft_memcpy(new_malloc, ptr, ft_min((int)size, (int)found_malloc->len));
		clear_allocated_mem(found_malloc);
		return (new_malloc);
	}
	return err ? NULL : malloc(size);
}