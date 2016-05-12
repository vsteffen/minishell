/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 16:20:59 by vsteffen          #+#    #+#             */
/*   Updated: 2016/03/15 18:28:43 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static char		*strjoin_secure(char *s1, char *s2)
{
	char	*join;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
	{
		join = ft_strdup(s2);
		return (join);
	}
	if (s2 == NULL)
	{
		join = ft_strdup(s1);
		ft_strdel(&s1);
		return (join);
	}
	if (s1 != NULL && s2 != NULL)
	{
		join = ft_strjoin(s1, s2);
		ft_strdel(&s1);
		return (join);
	}
	return (NULL);
}

static int		newline_detected(char *stbuff, char **line)
{
	char			*nl;

	nl = ft_strchr(stbuff, '\n');
	*line = ft_strsub(stbuff, 0, nl - stbuff);
	ft_strcpy(stbuff, nl + 1);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	static char		*stbuff[2147483647];
	int				ret;

	if (line == NULL || fd < 0)
		return (-1);
	if ((ft_strchr(stbuff[fd], '\n') != NULL) && stbuff[fd] && stbuff[fd][0])
		return (newline_detected(stbuff[fd], line));
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if ((stbuff[fd] = strjoin_secure(stbuff[fd], buff)) == NULL)
			return (-1);
		if (ft_strchr(stbuff[fd], '\n') != NULL)
			return (newline_detected(stbuff[fd], line));
	}
	if (ret == -1)
		return (-1);
	if (stbuff[fd] && *(stbuff[fd]))
	{
		*line = ft_strdup(stbuff[fd]);
		ft_strdel(&(stbuff[fd]));
		return (1);
	}
	return (0);
}
