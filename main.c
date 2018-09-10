/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 12:30:43 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/10 11:49:41 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_mmmeta	*init_mmmmeta(void)
{
	t_mmmeta *mmmeta;

	mmmeta = (t_mmmeta *)mmap(NULL, sizeof(t_mmmeta), PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	mmmeta->medium = NULL;
	mmmeta->small = NULL;
	return mmmeta;
}

// return the optimal size for a new mmeta allocation, commanded_size should be SMALL, MEDIUM or LARGE
size_t		get_optimal_size(int commanded_size)
{
	int initial;
	
	initial = commanded_size * 100 + sizeof(t_meta) * 100 + sizeof(t_mmeta);
	return initial + initial % PAGE_SIZE;
}

t_meta		*init_meta(t_meta	*prev, int commanded_size)
{
	t_meta	*meta;

	meta = prev + (commanded_size + sizeof(t_meta));
	meta->is_free = 1;
	meta->next = NULL;
	return meta;
}
// commanded_size should be SMALL, MEDIUM or LARGE
t_mmeta		*init_mmeta(int commanded_size)
{
	t_mmeta	*mmeta;

	//todo: allocate more space than just the struct
	mmeta = (t_mmeta *)mmap(NULL, get_optimal_size(commanded_size), PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	mmeta->head = init_meta((t_meta *)mmeta, commanded_size);
	mmeta->available_space = commanded_size - (sizeof(t_mmeta) + sizeof(t_meta) * 100);//todo: get real space;
	return mmeta;
}

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
