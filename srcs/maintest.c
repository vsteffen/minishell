/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 17:17:11 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/27 20:19:12 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_arg(char **arg)
{
	int		i;

	i = 0;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		i++;
	}
	free(arg[i]);
	free(arg);
}

void		struct_ini(t_d *d, char **env)
{
	d->env_end = NULL;
	d->pwd = NULL;
	d->oldpwd = NULL;
	d->shlvl = NULL;
	d->home = NULL;
	d->shell = NULL;
	d->exec = malloc(sizeof(d->exec));
	d->exec[0] = NULL;
	d->new_env = malloc(sizeof(d->new_env));
	d->new_env[0] = NULL;
	d->cmd_status = 1;
	d->lst_env = env_to_list(env, d, 0, NULL);
	signal(2, SIG_IGN);
	print_bash(d);
}

int			ft_isbuiltin(t_d *d)
{
	if (ft_strequ(d->buff[0], "exit"))
	{
		free_arg(d->buff);
		exit(0);
	}
	if (ft_strequ(d->buff[0], "setenv"))
		return (ft_setenv(d, 1));
	if (ft_strequ(d->buff[0], "env"))
		return (ft_env(d->lst_env));
	if (ft_strequ(d->buff[0], "unsetenv"))
		return (ft_unsetenv(d, 1));
	if (ft_strequ(d->buff[0], "cd"))
		return (ft_cd(d));
	return (0);
}

void		main2(t_d *d)
{
	d->cmd_status = 0;
	ft_superstr("zsh: command not found: \"", d->buff[0], "\"\n", NULL);
}

int			main(int ac, char **av, char **env)
{
	t_d			d;
	char		*oldptr;

	oldptr = NULL;
	av[ac] = av[ac];
	struct_ini(&d, env);
	while (get_next_line(0, &(d.gnl_buff)))
	{
		if (d.gnl_buff == oldptr)
			return (-1);
		oldptr = d.gnl_buff;
		d.buff = transform_str(&d, 0, 0);
		if (ft_isbuiltin(&d))
		{
		}
		else if (try_execve(&d))
			launch_execve(&d);
		else
		{
			if (d.buff[0] != NULL)
				main2(&d);
		}
		free_arg(d.buff);
		print_bash(&d);
	}
}
