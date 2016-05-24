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
