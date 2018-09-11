/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 12:31:57 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/11 14:06:22 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>

typedef struct	s_large_mmap
{
	struct s_large_mmap	*next;
}				t_large_mmap;

typedef struct	s_malloc
{
	unsigned char 	is_free;
	size_t			len;
	void			*next;
}			t_malloc;

typedef struct	s_m_mmap
{
    t_malloc 			*head;
	struct s_m_mmap		*next;
	size_t				free_bits;
}			t_m_mmap;

typedef struct	s_manager
{
	t_m_mmap		*tiny;
    t_m_mmap 		*small;
	t_large_mmap	*large;
}				t_manager;

#define TINY 32
#define SMALL 64
#define NB_CHUNKS 100
#define PAGE_SIZE (getpagesize())

t_malloc		*init_malloc(t_malloc	*prev, int chunk_size);
t_m_mmap		*init_m_mmap(int chunk_size);
t_manager		*init_manager(void);
t_large_mmap	*init_large_mmap(size_t req_size);
void			show_alloc_mem(void);