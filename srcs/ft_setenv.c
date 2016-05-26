/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 14:51:00 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/26 21:08:55 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		key_exist(t_lst *list, char *key, char *value, t_d *d)
{
	while (list)
	{
		if (ft_strequ(key, list->key))
		{
			get_key_important(d, key, value);
			free(key);
			free(list->value);
			list->value = value;
			return (1);
		}
		list = list->next;
	}
	return (0);
}

void ft_add_env(t_d *d, char *key, char *value)
{
	t_lst		*list;

	if (!d->lst_env)
	{
		list = lst_new(d, NULL, key, value);
		d->lst_env = list;
		d->env_end = list;
	}
	else
	{
		list = d->env_end;
		list->next = lst_new(d, NULL, key, value);
		d->env_end = list->next;
	}
}

int	 	ft_setenv(t_d *d)
{
	int	arg;
	char *ptr;
	char *key;
	char *value;

	arg = 1;
	if_no_arg(d, d->buff[arg], 1);
	while (d->buff[arg] != '\0')
	{
		ptr = ft_strchr(d->buff[arg], '=');
		if (ptr == NULL || d->buff[arg][0] == '=')
		{
			ft_superstr("Invalid key or value for \"", d->buff[arg], "\"\nUsage: setenv key=value\n", NULL);
			d->cmd_status = 0;
			arg++;
			continue ;
		}
		key = ft_strsub(d->buff[arg], 0, ptr - d->buff[arg]);
		value = ft_strdup(ptr + 1);
		if (key_exist(d->lst_env, key, value, d))
		{
			arg++;
			continue ;
		}
		else
			ft_add_env(d, key, value);
		arg++;
	}
	return (1);
}
