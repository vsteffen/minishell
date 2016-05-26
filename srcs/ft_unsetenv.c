/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:02:28 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/26 21:09:03 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		unsetenv_check_lst(t_lst *list, t_d *d, char *key, int *arg)
{
	t_lst *after;

	while (list->next)
	{
		if (list->next)
		{
			if (ft_strequ(key, list->next->key))
			{
				reset_key_important(d, key);
				free(list->next->key);
				free(list->next->value);
				after = list->next->next;
				free(list->next);
				list->next = after;
				if (list->next == NULL)
					d->env_end = list;
				printf("the key %s have been deleted\n", key);
				(*arg)++;
				return (1);
			}
			else
				list = list->next;
		}
	}
	return (0);
}

int	ft_unsetenv(t_d *d)
{
	t_lst		*list;
	int			arg;

	arg = 1;
	if_no_arg(d, d->buff[arg], 0);
	while (d->buff[arg] != '\0' && d->lst_env)
	{
		list = d->lst_env;
		if (ft_strequ(list->key, d->buff[arg]))
		{
			reset_key_important(d, d->buff[arg]);
			free(list->key);
			free(list->value);
			d->lst_env = list->next;
			free(list);
			arg++;
			continue ;
		}
		if (!(unsetenv_check_lst(list, d, d->buff[arg], &arg)))
		{
			ft_superstr("Key \"", d->buff[arg], "\" not found\n", NULL);
			d->cmd_status = 0;
			arg++;
		}
	}
	return (1);
}
