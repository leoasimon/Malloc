/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 14:04:12 by ekelen            #+#    #+#             */
/*   Updated: 2018/09/23 11:39:12 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void			*get_next(t_block *curr)
{
	if (curr && curr->is_free)
		return (get_next(curr->next));
	return (curr);
}

static void			*find_alloc_in_list(void *ptr, t_block *curr, t_block *s)
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

static void			*free_and_update(t_zone *curr, void *ptr)
{
	t_block	*found_ptr;
	t_zone		*next;

	if (curr)
	{
		if (ptr > (void *)curr && ptr < (void *)curr + curr->len)
		{
			found_ptr = (t_block *)find_alloc_in_list(ptr, curr->head, NULL);
			if (found_ptr)
			{
				if (found_ptr == curr->head && found_ptr->next == NULL && \
				curr->free_bytes < SMALL)
				{
					next = curr->next;
					munmap(curr, curr->len + sizeof(t_block));
					return (next);
				}
				found_ptr->is_free = 1;
			}
			return (curr);
		}
		curr->next = free_and_update(curr->next, ptr);
	}
	return (curr);
}

static void			*free_and_update_lg(t_block *curr, void *ptr)
{
	t_block	*next;

	if (curr)
	{
		if (curr->ret_ptr == ptr)
		{
			next = curr->next;
			munmap(curr, sizeof(t_block) + curr->len);
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
