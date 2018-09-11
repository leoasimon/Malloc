/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 12:30:43 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/11 14:14:01 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
t_manager	*manager = NULL;


t_m_mmap	*get_linked(t_m_mmap *curr, size_t chunk_size)
{
	printf("hello + %zu\n", chunk_size);
	if (!curr)
		return init_m_mmap(chunk_size);
	if (!curr->free_bits)
		curr->next = get_linked(curr->next, chunk_size);
	return curr;
}

t_large_mmap	*add_large_node(t_large_mmap *curr, size_t req_size)
{
	if (!curr)
		return init_large_mmap(req_size);
	curr->next = add_large_node(curr->next, req_size);
	return curr;
}

void		*retrieve_large_tail(t_large_mmap *curr)
{
	if (!curr->next)
		return curr;
	return retrieve_large_tail(curr->next);
}

//At this point, our m_mmap has some avalaible space
// void	*retrieve_chunk(t_m_mmap *m_mmap, size_t s)
// {
// 	t_malloc	*block;
// 	block = m_mmap->head;
// }

//At this point an available m_mmap should exist, no mmap call would be necessary
t_m_mmap	*retrieve_available_mmap(t_m_mmap *curr)
{
	if (curr->free_bits) return curr;
	return retrieve_available_mmap(curr->next);
}

void	*ft_malloc(size_t	req_size)
{
	static int		debug_count = 0;

	debug_count++;
	//Check if the base manager exists
	if (manager == NULL)
		manager = init_manager();
	// Check size_t to know if we deal with SMALL, SMALL or LARGE, 
	//...go for a nice function pointer array ?...
	if (req_size <= TINY)
	{
		manager->tiny = get_linked(manager->tiny, TINY);
		// retrieve_chunk(retrieve_available_mmap(manager->tiny), req_size);
	}
	if (req_size <= SMALL)
	{
		manager->small = get_linked(manager->small, SMALL);
		// retrieve_chunk(retrieve_available_mmap(manager->small), req_size);
	}
	if (req_size > SMALL)
	{
		manager->large = add_large_node(manager->large, req_size);// check if we already have list of large mmaps
		// attach address of large to list of larges
		// return head of list
		return NULL;
		// return (retrieve_large_tail(manager->large));
	}
	return NULL;
}

void print_large_mmap(t_large_mmap *curr, int i)
{
	if (curr)
	{
		printf("%d: %p\n", i, curr);
		print_large_mmap(curr->next, i + 1);
	}
}
int	main(void)
{
	void	*alloc;
	// alloc = ft_malloc(200);


	for (int i = 0; i < 15; i++) {
		alloc = ft_malloc(200);
	}
	print_large_mmap(manager->large, 1);
	// show_alloc_mem();
	return (1);
}
