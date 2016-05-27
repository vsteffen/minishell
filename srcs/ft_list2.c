/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 16:40:54 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/27 16:41:05 by vsteffen         ###   ########.fr       */
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

void	get_exec_tab(t_d *d, char *value)
{
	char	*ptr;

	ptr = ft_strchr(value, '=');
	d->exec = ft_strsplit(value, ':');
}

void	reset_exec_tab(t_d *d, char *value, int status)
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
