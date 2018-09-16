/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 09:43:28 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/15 15:53:47 by ekelen           ###   ########.fr       */
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

void clear_allocated_mem(t_malloc	*ptr)
{
	ptr->is_free = 1;
	ft_bzero(ptr->ret_ptr, ptr->len);
}

// void split_mem(t_malloc	*ptr, size_t new_size)
// {
// 	t_malloc	*new_block;

void	*realloc(void	*ptr, size_t size)
{
	t_malloc	*found_ptr;
	size_t		available_space;
	t_malloc	*new_malloc;
	
	found_ptr = locate_ptr_in_heaps(ptr);
	if (found_ptr)
	{
		printf("found: %p, %zu\n", ptr, size);
		if (size <= found_ptr->len) 
		{
			available_space = (found_ptr)->len - MALLOC_STRUCT_SIZE - size;
			if (available_space >= 4) 
			{
				// TODO: split
				return (found_ptr);
			}
			return (found_ptr);
		}
		// if (available_space > 4)
		new_malloc = malloc(size);
		ft_memcpy(new_malloc, found_ptr, size);
		clear_allocated_mem(ptr);
		return new_malloc;
	}
	//if ptr not found, null, just return a new malloc
	return malloc(size);
}