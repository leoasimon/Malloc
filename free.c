/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 12:41:20 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/17 09:37:50 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_manager	*manager;

static void	*get_next(t_malloc	*curr)
{
	if (curr && curr->is_free)
		return get_next(curr->next);
	return curr;
}

static void	*find_alloc_in_list(void *ptr, t_malloc *curr, t_malloc *start)
{
    if (!curr)
        return NULL;
    if (ptr == curr->ret_ptr)
	{
		start = start ? start : curr;
		start->next = get_next(curr->next);
        return start;
	}
	if (curr->is_free && !start)
		start = curr;
	if (!curr->is_free)
		start = NULL;
    return find_alloc_in_list(ptr, curr->next, start);
}

static void clear_allocated_mem(t_malloc	*ptr)
{
	void	*p;
	
	p = ptr->ret_ptr;
	ptr->is_free = 1;
	ft_bzero(ptr->ret_ptr, ptr->len);
}

static void	*free_and_update(t_stock *curr, void *ptr)
{
	t_malloc	*found_ptr;
	t_stock		*next;
	
	if (curr)
	{
		if 
		(
			(void *)ptr > (void *)curr && 
			(void *)ptr < (void *)curr + curr->len
		)
		{
			found_ptr = (t_malloc *)find_alloc_in_list(ptr, curr->head, NULL);
			if (found_ptr == curr->head && found_ptr->next == NULL)
			{
				next = curr->next;
				munmap(curr, curr->len);
				return next;
			}
			clear_allocated_mem(found_ptr);
			return curr;
		}
		curr->next = free_and_update(curr->next, ptr);
	}
	return curr;
}

static void	*free_and_update_lg(t_malloc *curr, void *ptr)
{
	t_malloc	*next;
	
	if (curr)
	{
		if (curr->ret_ptr == ptr)
		{
			next = curr->next;
			munmap(curr, MALLOC_STRUCT_SIZE + curr->len);
			return next;
		}
		curr->next = free_and_update_lg(curr->next, ptr);
	}
	return curr;
}

void	free(void	*ptr)
{
	manager->large = free_and_update_lg(manager->large, ptr);
	manager->small = free_and_update(manager->small, ptr);
	manager->tiny = free_and_update(manager->tiny, ptr);
}