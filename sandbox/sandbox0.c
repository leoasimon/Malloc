/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 10:22:03 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/15 17:10:58 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../malloc.h"

int	main(void)
{
	char	*str = NULL;
	char	*str2 = NULL;

	str = (char *)malloc(10);
	str2 = (char *)malloc(10);
	return(0);
}