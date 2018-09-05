/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 08:18:37 by lsimon            #+#    #+#             */
/*   Updated: 2016/11/09 11:29:29 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*tmp;
	t_list	*tmp2;

	if (!lst || !f)
		return (NULL);
	tmp = f(lst);
	if ((new = ft_lstnew(tmp->content, tmp->content_size)))
	{
		tmp2 = new;
		lst = lst->next;
		while (lst)
		{
			tmp = f(lst);
			if (!(tmp2->next = ft_lstnew(tmp->content, tmp->content_size)))
				return (NULL);
			tmp2 = tmp2->next;
			lst = lst->next;
		}
	}
	return (new);
}
