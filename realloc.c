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

static t_stock *in_list(void *ptr, t_stock *curr)
{
	if (!curr) return NULL;
	if (
		ptr > (void *)curr && 
		ptr <= (void *)curr + curr->len &&
		!curr->is_free)
		{
			return curr;
		}
	return in_list(ptr, curr->next);
}

static t_malloc	*locate_ptr(void *ptr, int *err)
{
	t_malloc *found_malloc;
	t_stock  *list;

	found_malloc = NULL;
	list = NULL;
	if (!manager) return NULL;
	if (manager->tiny && (list = in_list(ptr, manager->tiny))) return (find_ptr_in_mallocs(ptr, list->head, err));
	else if (manager->small && (list = in_list(ptr, manager->small))) return (find_ptr_in_mallocs(ptr, list->head, err));
	else if (manager->large && !found_malloc) return (find_ptr_in_mallocs(ptr, manager->large, err));
	else
		return NULL;
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
	printf("---------\n");
	
	new_malloc = NULL;
	err = 0;
	
	
	found_malloc = locate_ptr(ptr, &err);
	printf("found_malloc           ::   %p\n", found_malloc);

	printf("ptr                    ::   %p\n", ptr);
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
	return (err > 0 ? NULL : malloc(size));
}