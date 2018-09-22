/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:37:55 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/22 13:06:03 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdio.h>
# include <unistd.h>

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

typedef enum	e_sizetype {
	TINY = 128,
	SMALL = 1204,
}				t_sizetype;

extern t_manager	g_manager;

# define TINY 128
# define SMALL 1204
# define NB_CHUNKS 100

void			*malloc(size_t req_size);
void			*realloc(void *ptr, size_t req_size);
void			free(void *ptr);
void			show_alloc_mem(void);

void			ft_putchar(char c);
void			ft_putstr(char *str);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_print_addr(void *addr);
void			ft_print_unsigned_long(size_t n);

void			*retrieve_large_tail(t_malloc *curr);
void			*get_ret_ptr(t_malloc *curr, size_t s, size_t *free_bits);
void			*ret_c(t_stock *stock, size_t req_size);

t_malloc		*init_malloc(void *addr, size_t req_size);
t_stock			*init_stock(int chunk_size);
t_malloc		*init_large_mmap(size_t req_size);

t_malloc		*get_updated_head(t_malloc *curr,\
				size_t req_size, void *pot_addr);

#endif
