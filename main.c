/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 12:30:43 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/10 12:00:27 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_meta		*get_available_node(t_meta	*curr, int commanded_size)
{
	if (curr->is_free) return curr;
	if (curr->next) return get_available_node(curr->next, commanded_size);
	return init_meta(curr, commanded_size);
}

void	*retrieve_space(t_mmeta	*curr, int commanded_size)
{
	t_meta	*node;
	
	node = NULL;
	if (curr == NULL)
		curr = init_mmeta(commanded_size);
	node = get_available_node(curr->head, commanded_size);
	return (node);
}

void	*ft_malloc(size_t	s)
{
	static t_mmmeta	*mmmeta = NULL;
	t_mmeta			*curr;

	curr = NULL;
	//Check if the base megastruct exists
	if (mmmeta == NULL)
		mmmeta = init_mmmmeta();
	// Check size_t to know if we deal with SMALL, MEDIUM or LARGE
	if (s <= SMALL)
		return retrieve_space(mmmeta->small, SMALL);
	if (s <= MEDIUM)
		return retrieve_space(mmmeta->medium, MEDIUM);
	// todo: large
	return NULL;
}

int	main(void)
{
	void	*alloc;

	alloc = ft_malloc(100);
	printf("allocated memory: %p\n", alloc);
	return (1);
}
