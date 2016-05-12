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
		get_next_line(0, &gnl_buff);
		printf("gnl_buff = %s\n", gnl_buff);
		if (strcmp(gnl_buff, "exit") == 0)
			exit(0);
	}
	father = fork();
	if (father > 0)
	{
		wait(0);
		printf("I'am your ... father ! ... BITCH\n");
	}
	if (father == 0)
	{
		sleep(1);
		execve("/bin/ls", av, NULL);
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
