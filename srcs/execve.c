/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 18:26:27 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/24 18:26:44 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_pathjoin(char const *s1, char const *s2)
{
	size_t	len_t;
	size_t	len_s1;
	char	*str_null;

	if (s1 && s2)
	{
		len_s1 = ft_strlen(s1);
		len_t = len_s1 + ft_strlen(s2) + 1;
		if (s1[0] == '/' && len_s1 == 1)
		{
			str_null = ft_strnew(len_t - 1);
			str_null[0] = '/';
			str_null = ft_strcat(str_null, s2);
			return (str_null);
		}
		str_null = ft_strnew(len_t);
		if (str_null)
		{
			str_null = ft_strcpy(str_null, s1);
			str_null[len_s1] = '/';
			str_null = ft_strcat(str_null, s2);
			return (str_null);
		}
	}
	return (NULL);
}

int   launch_execve(t_d *d, pid_t father)
{
  father = fork();

  if (father == 0)
    wait(0);
  if (father > 0)
  {
    execve(d->path, d->buff, NULL);
      return (1);
  }
  free(d->path);
  if (father > 0)
      kill(father, SIGKILL);
  return (0);
}

int   try_execve(t_d *d)
{
  int   i;

  i = 0;
  if (d->buff[0])
  {
    while (d->exec[i])
    {
      d->path = ft_pathjoin(d->exec[i], d->buff[0]);
      if (access(d->path, X_OK) == 0)
        return (1);
      free(d->path);
      i++;
    }
  }
  return (0);
}
