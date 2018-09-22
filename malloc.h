/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:37:55 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/22 14:37:27 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdio.h>
# include <unistd.h>

# define NB_CHUNKS 100

typedef struct		s_malloc
{
	unsigned char		is_free;
	size_t				len;
	void				*ret_ptr;
	struct s_malloc		*next;
}					t_malloc;

typedef struct		s_stock
{
	t_malloc			*head;
	struct s_stock		*next;
	size_t				free_bits;
	size_t				len;
}					t_stock;

typedef struct		s_manager
{
	t_stock		*tiny;
	t_stock		*small;
	t_malloc	*large;
}					t_manager;

typedef enum		e_stype {
	TINY = 128,
	SMALL = 1204,
}					t_stype;

extern t_manager	g_manager;

void				ft_putchar(char c);
void				ft_print_addr(void *addr);
void				ft_print_unsigned_long(size_t n);
void				ft_putstr(char *str);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*malloc(size_t req_size);
void				*realloc(void *ptr, size_t req_size);
void				free(void *ptr);
void				show_alloc_mem(void);
t_malloc			*add_large_node(t_malloc *curr, size_t req_size, int *err);
void				*retrieve_large_tail(t_malloc *curr);
t_malloc			*get_updated_head(t_malloc *curr, size_t rsz, void *addr);
void				*retrieve_chunk(t_stock *stock, size_t req_size);
t_stock				*get_usable_stock(t_stock *curr, size_t req_size);
t_malloc			*init_malloc(void *addr, size_t req_size);
t_stock				*init_stock(t_stype chunk_size);

#endif
