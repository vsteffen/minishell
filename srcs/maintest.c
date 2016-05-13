/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 17:17:11 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/12 23:47:23 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void sig_fpe(int sig)
{
	printf("PASSED IN SIG_FPE\n");
}

int		main(int ac, char **av)
{
	char	buf[1];
	char	*buff;
	pid_t		father;
	char	*gnl_buff;

	while (1)
	{
		ft_color_style(FG_YELLOW, "ʕ•́ᴥ•̀ʔっ ➜  ");
		get_next_line(0, &gnl_buff);
		printf("gnl_buff = %s\n", gnl_buff);
		if (strcmp(gnl_buff, "exit") == 0)
			exit(0);
		father = fork();
		printf("father = %d\n", father);
		if (father > 0)
		{
		//	wait(0);
		//	printf("I'am your ... father = %d ... BITCH !\n", father);
		}
		if (father == 0)
		{
			//execve("/bin/ls", av, NULL);
			//kill(father, SIGKILL);
		}
		kill(father, SIGKILL);
		ft_putchar('\n');
}
/*	if (signal(SIGFPE, sig_fpe) == SIG_ERR)
	{
		printf("Le gestionnaire de signal pour SIG_FPE n'a pu etre defini.");
	}
	else
	{
		printf("Le gestionnaire de signal pour SIG_FPE a pu etre defini.");
	}
	return (0);
*/
}
