/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:08:07 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/26 21:08:32 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cd(t_d *d)
{
	t_lst		*list;
	char		*dest;
	char		*old;
	size_t		size;

	list = d->lst_env;
	dest = NULL;
	if (!d->buff[1])
	{
		while (list)
		{
			if (ft_strequ("HOME", list->key))
			{
				dest = list->value;
				list = NULL;
				continue ;
			}
			list = list->next;
		}
		if (dest == NULL)
		{
			ft_putstr("cd: HOME not set\n");
			d->cmd_status = 0;
			return (1);
		}
	}
	else if (ft_strequ(d->buff[1], "-"))
	{
		while (list)
		{
			if (ft_strequ("OLDPWD", list->key))
			{
				dest = list->value;
				list = NULL;
				continue ;
			}
			list = list->next;
		}
		if (dest == NULL)
		{
			ft_putstr("cd: OLDPWD not set\n");
			d->cmd_status = 0;
			return (1);
		}
	}
	else
		dest = d->buff[1];
	if (!(old = (char *)malloc(sizeof(size))))
		ft_exit_prog("Fail to malloc buff for old path\n", FG_RED, 0);
	old = getcwd(NULL, 255);
	if (chdir(dest) == -1)
	{
		d->cmd_status = 0;
		ft_superstr("cd: ", dest, ": no such directory or permission denied\n",
		NULL);
		return (1);
	}
	dest = getcwd(NULL, 255);
	list = d->lst_env;
	while (list)
	{
		if (ft_strequ("OLDPWD", list->key))
		{
			free(list->value);
			list->value = old;
		}
		if (ft_strequ("PWD", list->key))
		{
			free(list->value);
			list->value = dest;
		}
		list = list->next;
	}
	return (1);
}
