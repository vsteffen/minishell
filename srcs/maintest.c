/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 17:17:11 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/15 20:26:57 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void sig_fpe(int sig)
{
	printf("PASSED IN SIG_FPE\n");
}

void print_bash(void)
{
	ft_color_style(FG_YELLOW, NULL, "ʕ•́ᴥ•̀ʔっ ➜  ", 0);
}

int		nb_param(char *gnl_buff)
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

void	transform_gnl(char *gnl_buff, char **arg)
{
	int		nb_arg;
	int		pos;
	int		deb;
	char	*strsub;
	char	**arg_prog;
	
	if (!(arg_prog = (char**)malloc(sizeof(char*) * (nb_param(gnl_buff) + 1))))
		ft_exit_prog("Fail to malloc new argv\n", FG_RED, 0);
	pos = 0;
	deb = 0;
	nb_arg = 0;
	while (gnl_buff[pos])//arg_prog[nb_arg])
	{
		while (ft_isspace(gnl_buff[pos]) && gnl_buff[pos] != '\0')
			pos++;
		if (!gnl_buff[pos])
			continue ;
		deb = pos;
		while (!ft_isspace(gnl_buff[pos]) && gnl_buff[pos] != '\0')
	//	{
	//		printf("%c ", gnl_buff[pos]);
			pos++;
	//	}
	//	printf("   /// pos = %d && pos - deb = %d\n", pos, pos - deb);
		//if (!(arg_prog[nb_arg] = (char *)malloc(sizeof(char) * (pos - deb + 1))))
		//	ft_exit_prog("Fail to malloc new tab of argv\n", FG_RED, 0);
		arg_prog[nb_arg] = ft_strsub(gnl_buff, deb, pos - deb);
		nb_arg++;
		pos++;
	}
	arg_prog[nb_arg] = NULL;
//	printf("strlen de strsub = %lu\n", strlen(strsub));
//	printf("	nb_arg = %d\n", nb_arg);
//	printf("strsub = \"%s\"\n", strsub);
}

int		main(int ac, char **av)
{
	char	buf[1];
	char	*buff;
	pid_t		father;
	char	*gnl_buff;

	char	**arg;
	char *foo[] = { "/bin/ls", "-l", NULL };
	//	printf("av[0] = %s\n", av[1]);
	//	av[0] = "/bin/ls";	
	//	ft_color_style(BG_LBLUE, NULL, "\n", 1);
	while (1)
	{
		print_bash();
		get_next_line(0, &gnl_buff);
		printf("gnl_buff = %s\n", gnl_buff);
		if (strcmp(gnl_buff, "exit") == 0)
			exit(0);
		transform_gnl(gnl_buff, &*arg);
	}
/*		father = fork();
		//printf("father = %d\n", father);
		if (father > 0)
		{
			wait(0);
			printf("I'am your ... father = %d ... BITCH !\n", father);
		}
		if (father == 0)
		{
			printf("FATHER == 0 !\n");
			if (access("/bin/ls", F_OK) == 0)
			{
				printf("\tACCESS OK !\n");
				//execve(foo[0], foo, NULL);
				//execve("/usr/bin/env", NULL, NULL);
				printf("strerror = \"%s\"\n", strerror(errno));
			}
			//kill(father, SIGKILL);
		}
		//	kill(father, SIGKILL);
		ft_putchar('\n');
	}
*/	/*	if (signal(SIGFPE, sig_fpe) == SIG_ERR)
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
