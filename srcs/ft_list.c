/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 14:59:36 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/26 21:08:48 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_key(char *env_line, int *end_key)
{
	*end_key = 0;
	if (env_line == NULL)
		return (NULL);
	while (env_line[*end_key] != '=')
		(*end_key)++;
	return (ft_strsub(env_line, 0, *end_key));
}

char	*get_env_value(char *env_line, int *end_key)
{
	int		pos;

	if (env_line == NULL)
		return (NULL);
	(*end_key)++;
	pos = *end_key;
	while (env_line[pos] != '\0')
		pos++;
	return (ft_strsub(env_line, *end_key, pos - 1));
}

void get_exec_tab(t_d *d, char *value)
{
	char 	*ptr;

	ptr = ft_strchr(value, '=');
	d->exec = ft_strsplit(value, ':');
}

void reset_exec_tab(t_d *d, char *value, int status)
{
	int	i;

	if (d->exec[0] == NULL && status == 0)
		return ;
	else
	{
		i = 0;
		while (d->exec[i])
		{
			free(d->exec[i]);
			i++;
		}
		free(d->exec[i]);
		free(d->exec);
		if (status == 0 || value == NULL)
		{
			d->exec = malloc(sizeof(d->exec));
			d->exec[0] = NULL;
		}
		else
			get_exec_tab(d, value);
	}
}

void get_key_important(t_d *d, char *key, char *value)
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
	//	if (ft_strequ(key, "PWD"))
	//		d->pwd = NULL;
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
	int				type;
	int				end_key;

	if (!(list = (t_lst*)malloc(sizeof(t_lst))))
		ft_exit_prog("Failed to initialize the linked list.\n", FG_RED, 0);
	if (!key)
		list->key = get_env_key(env_line, &end_key);
	else
		list->key = key;
	if (!key) // !key only ???
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
