/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 14:59:36 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/27 16:40:06 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_key_important(t_d *d, char *key, char *value)
{
	if (ft_strequ(key, "PWD"))
		d->pwd = value;
	else if (ft_strequ(key, "OLDPWD"))
		d->oldpwd = value;
	else if (ft_strequ(key, "SHLVL"))
		d->shlvl = value;
	else if (ft_strequ(key, "HOME"))
		d->home = value;
	else if (ft_strequ(key, "SHELL"))
		d->shell = value;
	else if (ft_strequ(key, "PATH"))
		reset_exec_tab(d, value, 1);
}

void	reset_key_important(t_d *d, char *key)
{
	if (ft_strequ(key, "OLDPWD"))
		d->oldpwd = NULL;
	else if (ft_strequ(key, "SHLVL"))
		d->shlvl = NULL;
	else if (ft_strequ(key, "HOME"))
		d->home = NULL;
	else if (ft_strequ(key, "SHELL"))
		d->shell = NULL;
	else if (ft_strequ(key, "PATH"))
		reset_exec_tab(d, NULL, 0);
}

t_lst	*lst_new(t_d *d, char *env_line, char *key, char *value)
{
	t_lst			*list;
	int				end_key;

	if (!(list = (t_lst*)malloc(sizeof(t_lst))))
		ft_exit_prog("Failed to initialize the linked list.\n", FG_RED, 0);
	if (!key)
		list->key = get_env_key(env_line, &end_key);
	else
		list->key = key;
	if (!key)
		list->value = get_env_value(env_line, &end_key);
	else
		list->value = value;
	if (!key)
		d->env_end = list;
	get_key_important(d, list->key, list->value);
	list->next = NULL;
	return (list);
}

t_lst	*add_elem(t_lst *list, t_d *d, char *env_line)
{
	if (!list)
	{
		list = lst_new(d, env_line, NULL, NULL);
		return (list);
	}
	list->next = lst_new(d, env_line, NULL, NULL);
	return (list->next);
}
