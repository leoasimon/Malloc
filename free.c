/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 11:12:43 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/20 14:21:47 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_manager	manager;

static void	*get_next(t_malloc *curr)
{
	if (curr && curr->is_free)
		return (get_next(curr->next));
	return (curr);
}

static void			*find_alloc_in_list(void *ptr, t_malloc *curr, t_malloc *s)
{
	if (!curr)
		return (NULL);
	if (ptr == curr->ret_ptr)
	{
		s = s ? s : curr;
		s->next = get_next(curr->next);
		return (s);
	}
	if (curr->is_free && !s)
		s = curr;
	if (!curr->is_free)
		s = NULL;
	return (find_alloc_in_list(ptr, curr->next, s));
}

static void			clear_allocated_mem(t_malloc *ptr)
{
	void	*p;

	p = ptr->ret_ptr;
	ptr->is_free = 1;
	ft_bzero(ptr->ret_ptr, ptr->len);
}

static void			*free_and_update(t_stock *curr, void *ptr)
{
	t_malloc	*found_ptr;
	t_stock		*next;

	if (curr)
	{
		if (ptr > (void *)curr && ptr < (void *)curr + curr->len)
		{
			found_ptr = (t_malloc *)find_alloc_in_list(ptr, curr->head, NULL);
			if (found_ptr)
			{
				if (found_ptr == curr->head && found_ptr->next == NULL)
				{
					next = curr->next;
					munmap(curr, curr->len + MALLOC_STRUCT_SIZE);
					return (next);
				}
				clear_allocated_mem(found_ptr);
			}
			return (curr);
		}
		curr->next = free_and_update(curr->next, ptr);
	}
	return (curr);
}

static void			*free_and_update_lg(t_malloc *curr, void *ptr)
{
	t_malloc	*next;

	if (curr)
	{
		if (curr->ret_ptr == ptr)
		{
			next = curr->next;
			munmap(curr, MALLOC_STRUCT_SIZE + curr->len);
			return (next);
		}
		curr->next = free_and_update_lg(curr->next, ptr);
	}
	return (curr);
}

void				free(void *ptr)
{
	g_manager.large = free_and_update_lg(g_manager.large, ptr);
	g_manager.small = free_and_update(g_manager.small, ptr);
	g_manager.tiny = free_and_update(g_manager.tiny, ptr);
}
