/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 12:31:57 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/18 10:48:09 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct	s_malloc
{
	unsigned char		is_free;
	size_t				len;
	struct s_malloc		*prev;
	void				*ret_ptr;
	struct s_malloc		*next;
}				t_malloc;

typedef struct	s_stock
{
	t_malloc			*head;
	struct s_stock		*next;
	size_t				free_bits;
	size_t				len;
}				t_stock;

typedef struct	s_manager
{
	t_stock		*tiny;
	t_stock		*small;
	t_malloc	*large;
}				t_manager;

enum {
	TINY = 128,
	SMALL = 1200,
} e_chunk_size;

# define TINY 128
# define SMALL 1200
# define NB_CHUNKS 100
# define PAGE_SIZE (getpagesize())
# define STOCK_STRUCT_SIZE (sizeof(t_stock))
# define MALLOC_STRUCT_SIZE (sizeof(t_malloc))

void			*malloc(size_t req_size);
void			*realloc(void *ptr, size_t req_size);
void			free(void *ptr);
void			show_alloc_mem(void);


t_malloc		*init_malloc(void *addr, size_t req_size);
t_stock			*init_stock(int chunk_size);
t_manager		*init_manager(void);
t_malloc		*init_large_mmap(size_t req_size);


#endif
