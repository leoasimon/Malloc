/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:37:55 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/23 12:14:47 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
// # include <stdio.h>
# include <unistd.h>

# define NB_CHUNKS 100
# define TINY 128
# define SMALL 1204

typedef struct		s_block
{
	unsigned char		is_free;
	size_t				len;
	void				*ret_ptr;
	struct s_block		*next;
}					t_block;

typedef struct		s_zone
{
	t_block				*head;
	struct s_zone		*next;
	size_t				free_bytes;
	size_t				len;
	void				*end;
	int					(*fits)(void*, void*, size_t);
}					t_zone;

typedef struct		s_manager
{
	t_zone		*tiny;
	t_zone		*small;
	t_block		*large;
}					t_manager;

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
t_block				*add_large_node(t_block *curr, size_t req_size, int *err);
void				*retrieve_large_tail(t_block *curr);
t_block				*get_updated_head(t_block *curr, size_t rsz, void *addr);
void				*retrieve_chunk(t_zone *zone, size_t req_size);
t_zone				*get_usable_zone(t_zone *curr, size_t req_size);
t_block				*init_block(void *addr, size_t req_size);
t_zone				*init_zone(size_t sizetype);

#endif
