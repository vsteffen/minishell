/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merdier.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 21:00:47 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/26 21:05:33 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void		print_bash(t_d *d)
{
	char *color;

	if (d->cmd_status == 0)
		color = FG_RED;
	else if (d->cmd_status == 1)
		color = FG_GREEN;
	else
		color = FG_YELLOW;
	ft_color_style(color, NULL, "ʕ•́ᴥ•̀ʔっ ➜  ", 0);
	d->cmd_status = 1;
}

int			nb_param(char *gnl_buff)
{
	int		nb;
	int		pos;

	pos = 0;
	nb = 0;
	while (gnl_buff[pos])
	{
		while (ft_isspace(gnl_buff[pos]) && gnl_buff[pos] != '\0')
			pos++;
		if (!gnl_buff[pos])
			continue ;
		while (!ft_isspace(gnl_buff[pos]) && gnl_buff[pos] != '\0')
			pos++;
		nb++;
	}
	return (nb);
}

char		**transform_str(t_d *d, int pos, int deb)
{
	char	**arg_prog;

	if (!(arg_prog = (char**)malloc(sizeof(char*) *
					(nb_param(d->gnl_buff) + 1))))
		ft_exit_prog("Fail to malloc new argv\n", FG_RED, 0);
	d->nb_arg = 0;
	while (d->gnl_buff[pos])
	{
		while (ft_isspace(d->gnl_buff[pos]) && d->gnl_buff[pos] != '\0')
			pos++;
		if (!d->gnl_buff[pos])
			continue ;
		deb = pos;
		while (!ft_isspace(d->gnl_buff[pos]) && d->gnl_buff[pos] != '\0')
			pos++;
		arg_prog[d->nb_arg] = ft_strsub(d->gnl_buff, deb, pos - deb);
		d->nb_arg++;
		if (!d->gnl_buff[pos])
			continue ;
		pos++;
	}
	arg_prog[d->nb_arg] = NULL;
	d->nb_arg--;
	return (arg_prog);
}
