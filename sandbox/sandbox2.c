/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 10:22:03 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/15 17:03:58 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../malloc.h"

int	main(void)
{
	char	*str;

	str = (char *)malloc(10);
	printf("ptr: %p\n", str);
	return(0);
}