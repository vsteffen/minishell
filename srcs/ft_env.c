/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 14:56:13 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/24 14:56:17 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_envjoin(char const *s1, char const *s2)
{
	size_t	len_t;
	size_t	len_s1;
	char	*str_null;

	if (s1 && s2)
	{
		len_s1 = ft_strlen(s1);
		len_t = len_s1 + ft_strlen(s2) + 1;
		if (s1[0] == '=' && len_s1 == 1)
		{
			str_null = ft_strnew(len_t - 1);
			str_null[0] = '=';
			str_null = ft_strcat(str_null, s2);
			return (str_null);
		}
		str_null = ft_strnew(len_t);
		if (str_null)
		{
			str_null = ft_strcpy(str_null, s1);
			str_null[len_s1] = '=';
			str_null = ft_strcat(str_null, s2);
			return (str_null);
		}
	}
	return (NULL);
}

void env_to_char(t_d *d)
{
	t_lst	*list;
	int	i;
	int	tmp;

	list = d->lst_env;
	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	tmp = 0;
	while (d->new_env[tmp])
	{
		free(d->new_env[tmp]);
	}
	free(d->new_env);
	if (!(d->new_env = (char**)malloc(sizeof(char*) * (i + 1))))
		ft_exit_prog("Fail to malloc new argv\n", FG_RED, 0);
	tmp = 0;
	list = d->lst_env;
	while (list)
	{
		d->new_env[tmp] = ft_envjoin(list->key, list->value);
		tmp++;
		list = list->next;
	}
	d->new_env[tmp] = NULL;
}

t_lst   *env_to_list(char **env, t_d *d, int i, t_lst *list)
{
	t_lst	*tmp;

	tmp = NULL;
	while (env[i])
	{
		list = add_elem(list, d, env[i]);
		if (i == 0)
			tmp = list;
		i++;
	}
	return (tmp);
}

int if_no_arg(t_d *d, char *first_arg, int status)
{
	if (!first_arg && status == 0)
	{
		ft_putstr("Specify a key to delete it\nUsage: unsetenv key\n");
		d->cmd_status = 0;
		return (0);
	}
	else if (!first_arg && status == 1)
	{
		ft_putstr("Specify a key with a value to add in environment\nUsage: setenv key=value\n");
		d->cmd_status = 0;
		return (0);
	}
	return (1);
}

int ft_env(t_lst *list)
{
	while (list)
	{
		ft_superstr(list->key, "=", list->value, "\n");
		list = list->next;
	}
	return (1);
}
