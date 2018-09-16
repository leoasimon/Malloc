/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 12:41:20 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/16 12:53:54 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_manager	*manager;

static void	*find_alloc_in_list(void *ptr, t_malloc *curr)
{
    if (!curr)
        return NULL;

	printf("ptr: %p, ret: %p\n\n", ptr, curr->ret_ptr);
    if (ptr == curr->ret_ptr)
        return curr;

    return find_alloc_in_list(ptr, curr->next);
}

static void	*locate_ptr(t_stock *curr, void *ptr)
{
	if (curr)
	{
		if 
		(
			(void *)ptr > (void *)curr && 
			(void *)ptr < (void *)curr + curr->len
		)
			return find_alloc_in_list(ptr, curr->head); //may not work with large
		return locate_ptr(curr->next, ptr);
	}
	return NULL;
}

static void	*locate_ptr_in_heaps(void	*ptr)
{
	void	*found_ptr;
	found_ptr = locate_ptr(manager->tiny, ptr);
	if (!found_ptr)
		found_ptr = locate_ptr(manager->small, ptr);
	if (!found_ptr)
		found_ptr = locate_ptr((t_stock *)manager->large, ptr); //Ugly cast
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