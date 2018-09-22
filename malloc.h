/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:37:55 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/22 12:42:01 by ekelen           ###   ########.fr       */
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

typedef enum {
	TINY = 128,
	SMALL = 1204,
} e_sizetype;

extern t_manager	g_manager;

# define TINY 128
# define SMALL 1204
# define NB_CHUNKS 100

void			ft_putchar(char c);
void			ft_print_addr(void *addr);
void			ft_print_unsigned_long(size_t n);
void			ft_putstr(char *str);

void			*malloc(size_t req_size);
void			*realloc(void *ptr, size_t req_size);
void			free(void *ptr);
void			show_alloc_mem(void);

t_malloc		*init_malloc(void *addr, size_t req_size);
t_stock			*init_stock(int chunk_size);
t_malloc		*init_large_mmap(size_t req_size);

#endif
