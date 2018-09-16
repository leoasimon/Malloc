/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 12:41:20 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/16 13:49:42 by lsimon           ###   ########.fr       */
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

static void	*locate_ptr(t_stock *curr, void *ptr, t_stock *last)
{
	t_malloc	*found_ptr;
	
	if (curr)
	{
		if 
		(
			(void *)ptr > (void *)curr && 
			(void *)ptr < (void *)curr + curr->len
		)
		{
			found_ptr = (t_malloc *)find_alloc_in_list(ptr, curr->head, NULL); //may not work with large
			if (found_ptr == curr->head && found_ptr->next == NULL)
			{
				if (last)
					last->next = curr->next;
				munmap(curr, curr->len);
				return NULL;
			}
			return found_ptr;
		}
		return locate_ptr(curr->next, ptr, curr);
	}
	return NULL;
}

static void	*locate_ptr_in_heaps(void	*ptr)
{
	void	*found_ptr;
	found_ptr = locate_ptr(manager->tiny, ptr, NULL);
	if (!found_ptr)
		found_ptr = locate_ptr(manager->small, ptr, NULL);
	if (!found_ptr)
		found_ptr = locate_ptr((t_stock *)manager->large, ptr, NULL); //Ugly cast
	return(found_ptr);
}

static void clear_allocated_mem(t_malloc	*ptr)
{
	ptr->is_free = 1;
	ft_bzero(ptr->ret_ptr, ptr->len);
}

void	free(void	*ptr)
{
	t_malloc	*found_ptr;
	
	found_ptr = locate_ptr_in_heaps(ptr);
	if (found_ptr)
		clear_allocated_mem(found_ptr);
	//if ptr not found, fail silently
}