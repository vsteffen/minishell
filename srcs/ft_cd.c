/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:08:07 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/27 16:26:57 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_cd2(t_d *d, char **dest, char **old)
{
	t_lst		*list;

	*dest = getcwd(NULL, 255);
	list = d->lst_env;
	while (list)
	{
		if (ft_strequ("OLDPWD", list->key))
		{
			free(list->value);
			list->value = *old;
		}
		if (ft_strequ("PWD", list->key))
		{
			free(list->value);
			list->value = *dest;
		}
		list = list->next;
	}
}

int			ft_cd3(t_d *d, char **dest)
{
	t_lst		*list;

	list = d->lst_env;
	while (list)
	{
		if (ft_strequ("HOME", list->key))
		{
			*dest = list->value;
			list = NULL;
			continue ;
		}
		list = list->next;
	}
	if (*dest == NULL)
	{
		ft_putstr("cd: HOME not set\n");
		d->cmd_status = 0;
		return (1);
	}
	return (0);
}

int			ft_cd4(t_d *d, char **dest)
{
	t_lst	*list;

	list = d->lst_env;
	while (list)
	{
		if (ft_strequ("OLDPWD", list->key))
		{
			*dest = list->value;
			list = NULL;
			continue ;
		}
		list = list->next;
	}
	if (*dest == NULL)
	{
		ft_putstr("cd: OLDPWD not set\n");
		d->cmd_status = 0;
		return (1);
	}
	return (0);
}

int			ft_cd5(t_d *d, char **dest)
{
	d->cmd_status = 0;
	ft_superstr("cd: ", *dest, ": no such directory or permission denied\n",
			NULL);
	return (1);
}

int			ft_cd(t_d *d)
{
	char		*dest;
	char		*old;

	dest = NULL;
	if (!d->buff[1])
	{
		if (ft_cd3(d, &dest))
			return (1);
	}
	else if (ft_strequ(d->buff[1], "-"))
	{
		if (ft_cd4(d, &dest))
			return (1);
	}
	else
		dest = d->buff[1];
	if (!(old = (char *)malloc(sizeof(255))))
		ft_exit_prog("Fail to malloc buff for old path\n", FG_RED, 0);
	old = getcwd(NULL, 255);
	if (chdir(dest) == -1)
		return (ft_cd5(d, &dest));
	ft_cd2(d, &dest, &old);
	return (1);
}
