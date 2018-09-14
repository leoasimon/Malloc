/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 14:22:19 by ekelen            #+#    #+#             */
/*   Updated: 2018/09/14 15:20:28 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
extern t_manager	*manager;

// TODO: Make less redundant
int             find_alloc_in_lg_list(void *ptr, t_large_mmap *curr)
{
    if (!ptr || !curr) {
        return 0;
    }

    if (ptr == curr->ret_ptr && !curr->is_free) {
        curr->is_free = 1;
        printf("munmapping space : %p  bytes : %zu", curr->ret_ptr, curr->len);
        munmap(curr->ret_ptr, curr->len);
        return 1;
    }
    return find_alloc_in_lg_list(ptr, curr->next);
}

int             find_alloc_in_list(void *ptr, t_malloc *curr, int *call_munmap)
{
    if (!ptr || !curr) {
        return 0;
    }

    if (ptr == curr->ret_ptr && !curr->is_free) {
        curr->is_free = 1;
        return 1;
    }

    if (!curr->is_free) {
        *call_munmap = 0;
    }
    return find_alloc_in_list(ptr, curr->next, call_munmap);
}

void       		free(void *ptr)
{
    int         result;
    int         call_munmap;

    result = 0;
    if (!ptr || !manager) return;
    if (manager->tiny) {
        result = find_alloc_in_list(ptr, manager->tiny->head, &call_munmap);
        // TODO: use call_munmap to decide if we should call munmap
        printf("result of searching TINY : %d", result);
    }
    if (!result && manager->small) {
        result = find_alloc_in_list(ptr, manager->small->head, &call_munmap);
        // TODO: use call_munmap to decide if we should call munmap
        printf("result of searching SMALL : %d", result);
    }
    printf("call munmap : %d", call_munmap);
    if (!result && manager->large) {
        result = find_alloc_in_lg_list(ptr, manager->large);
        printf("result of searching LARGE : %d", result);
    }
    return ;
}