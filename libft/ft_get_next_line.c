/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 13:16:42 by lsimon            #+#    #+#             */
/*   Updated: 2016/12/15 13:40:35 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		last_line(char **line, char **buf)
{
	if (**buf)
	{
		*line = *buf;
		*buf = NULL;
		return (1);
	}
	*line = ft_strnew(0);
	return (0);
}

static int		next_line(int fd, char **line, char **buf)
{
	char		buffer[BUFF_SIZE + 1];
	char		*tmp;
	int			ret;

	while ((ret = read(fd, buffer, BUFF_SIZE)))
	{
		buffer[ret] = '\0';
		if (ret == -1)
			return (-1);
		if ((tmp = ft_strchr(buffer, '\n')))
		{
			*tmp = '\0';
			if ((*line = ft_strjoin(*buf, buffer)) == NULL
				|| (tmp = ft_strjoin(tmp + 1, "\0")) == NULL)
				return (-1);
			free(*buf);
			*buf = tmp;
			return (1);
		}
		if ((tmp = ft_strjoin(*buf, buffer)) == NULL)
			return (-1);
		free(*buf);
		*buf = tmp;
	}
	return (last_line(line, buf));
}

int				ft_get_next_line(int fd, char **line)
{
	static char	*buf;
	char		*tmp;

	if (buf)
	{
		if ((tmp = ft_strchr(buf, '\n')))
		{
			*tmp = '\0';
			if ((*line = ft_strjoin(buf, "\0")) == NULL
				|| (tmp = ft_strjoin(tmp + 1, "\0")) == NULL)
				return (-1);
			free(buf);
			buf = tmp;
			return (1);
		}
	}
	else
	{
		if ((buf = (char *)malloc(sizeof(char))) == NULL)
			return (-1);
		*buf = '\0';
	}
	return (next_line(fd, line, &buf));
}
