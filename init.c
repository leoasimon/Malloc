/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 11:52:59 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/10 11:58:28 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"


// return the optimal size for a new mmeta allocation, commanded_size should be SMALL, MEDIUM or LARGE
static size_t	get_optimal_size(int commanded_size)
{
	int initial;
	
	initial = commanded_size * 100 + sizeof(t_meta) * 100 + sizeof(t_mmeta);
	return initial + initial % PAGE_SIZE;
}

t_meta			*init_meta(t_meta	*prev, int commanded_size)
{
	t_meta	*meta;

	meta = prev + (commanded_size + sizeof(t_meta));
	meta->is_free = 1;
	meta->next = NULL;
	return meta;
}

// commanded_size should be SMALL, MEDIUM or LARGE
t_mmeta			*init_mmeta(int commanded_size)
{
	t_mmeta	*mmeta;

	mmeta = (t_mmeta *)mmap(NULL, get_optimal_size(commanded_size), PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	mmeta->head = init_meta((t_meta *)mmeta, commanded_size);
	mmeta->available_space = commanded_size - (sizeof(t_mmeta) + sizeof(t_meta) * 100);//todo: get real space;
	return mmeta;
}

t_mmmeta		*init_mmmmeta(void)
{
	t_mmmeta *mmmeta;

	mmmeta = (t_mmmeta *)mmap(NULL, sizeof(t_mmmeta), PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	mmmeta->medium = NULL;
	mmmeta->small = NULL;
	return mmmeta;
}