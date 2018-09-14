/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 12:31:57 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/14 14:55:32 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

#include <sys/mman.h>
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include "libft/libft.h"

typedef struct	s_large_mmap
{
	unsigned char		is_free;
	struct s_large_mmap	*next;
	void				*ret_ptr;
	size_t				len;
}				t_large_mmap;

typedef struct	s_malloc
{
	unsigned char 	is_free;
	size_t			len;
	struct s_malloc			*next;
	void			*ret_ptr;
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

#define TINY 128
#define SMALL 1200
#define NB_CHUNKS 100
#define PAGE_SIZE (getpagesize())
#define MMAP_STRUCT_SIZE (sizeof(t_m_mmap))
#define MMAP_LG_STRUCT_SIZE (sizeof(t_large_mmap))
#define MALLOC_STRUCT_SIZE (sizeof(t_malloc))
#define GET_NEXT_MALLOC_ADDR(x) ((void *)x + MALLOC_STRUCT_SIZE + x->len)

void			*malloc(size_t	req_size);
void       		free(void *ptr);
t_malloc		*init_malloc(void *addr, int size);
t_m_mmap		*init_m_mmap(int chunk_size);
t_manager		*init_manager(void);
t_large_mmap	*init_large_mmap(size_t req_size);
void			show_alloc_mem(void);


#endif