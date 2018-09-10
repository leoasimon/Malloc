/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 12:31:57 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/10 11:56:18 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>

typedef struct	s_meta
{
	unsigned char 	is_free;
	int				len;
	void			*next;
}			t_meta;

typedef struct	s_mmeta
{
    t_meta *head;
    int     available_space;
}			t_mmeta;

typedef struct	s_mmmeta
{
    t_mmeta	*medium;
    t_mmeta *small;
}				t_mmmeta;

#define SMALL 64
#define MEDIUM 180
#define PAGE_SIZE (getpagesize())

t_meta			*init_meta(t_meta	*prev, int commanded_size);
t_mmeta			*init_mmeta(int commanded_size);
t_mmmeta		*init_mmmmeta(void);