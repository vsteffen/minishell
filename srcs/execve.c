/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 18:26:27 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/27 20:04:38 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pathjoin(char const *s1, char const *s2)
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

int		launch_execve(t_d *d)
{
	int			status;
	pid_t		son;

	if (d->cmd_status == 0)
		return (0);
	son = fork();
	if (son != 0)
	{
		waitpid(son, &status, 0);
		if (WIFEXITED(status))
			if (WEXITSTATUS(status) != 0)
				d->cmd_status = 0;
	}
	else
	{
		signal(2, SIG_DFL);
		env_to_char(d, 0, 0);
		if (execve(d->path, d->buff, d->new_env) == -1)
			exit(1);
		return (1);
	}
	signal(2, SIG_IGN);
	free(d->path);
	return (0);
}

int		try_execve2(t_d *d)
{
	t_stat		stat;
	int			ret;

	d->path = ft_strdup(d->buff[0]);
	if (access(d->path, X_OK) == 0)
	{
		ret = lstat(d->path, &(stat));
		if (S_ISDIR(stat.st_mode))
		{
			ft_superstr("zsh: ", d->path, ": is a directory\n", NULL);
			d->cmd_status = 0;
		}
		return (1);
	}
	return (0);
}

int		try_execve(t_d *d)
{
	int		i;
	char	*ptr;

	i = 0;
	if (d->buff[0])
	{
		if ((ptr = ft_strchr(d->buff[0], '/')))
		{
			if (try_execve2(d))
				return (1);
		}
		else
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
	}
	return (0);
}
