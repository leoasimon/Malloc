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
#include <stdio.h>
#include <stdlib.h>

#define M (1024 * 1024)

int	main(void)
{
	char *addr1;
   char *addr3;

   addr1 = (char*)malloc(16*1024);
   strcpy(addr1, "Bonjours\n");
   printf("addr1 :: %p", addr1);
   addr3 = (char*)realloc(addr1, 128*M);
   addr3[127*M] = 42;
   printf("addr3 :: %p", addr1);
   return (0);
}