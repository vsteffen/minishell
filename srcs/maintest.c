/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 17:17:11 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/19 19:29:35 by vsteffen         ###   ########.fr       */
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

void	print_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
	{
		printf("tab[%d] = \"%s\"\n", i, tab[i]);
		i++;
	}

}

char		**transform_str(char *gnl_buff, t_d *d, int pos, int deb)
{
	char	**arg_prog;

	if (!(arg_prog = (char**)malloc(sizeof(char*) * (nb_param(gnl_buff) + 2))))
		ft_exit_prog("Fail to malloc new argv\n", FG_RED, 0);
	d->nb_arg = 1;
	while (gnl_buff[pos])
	{
		while (ft_isspace(gnl_buff[pos]) && gnl_buff[pos] != '\0')
			pos++;
		if (!gnl_buff[pos])
			continue ;
		deb = pos;
		while (!ft_isspace(gnl_buff[pos]) && gnl_buff[pos] != '\0')
			pos++;
		arg_prog[d->nb_arg] = ft_strsub(gnl_buff, deb, pos - deb);
		d->nb_arg++;
		if (!gnl_buff[pos])
			continue ;
		pos++;
	}
	arg_prog[d->nb_arg] = NULL;
	d->nb_arg--;
	return (arg_prog);
}

void		free_arg(char **arg)
{
	int		i;

	i = 0;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		i++;
	}
	free(arg);
	//	printf("SUCCESS FOR FREE\n");
}

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

t_lst	*lst_new(t_d *d, char *env_line)
{
	t_lst			*list;
	int				type;
	int				end_key;

	if (!(list = (t_lst*)malloc(sizeof(t_lst))))
		ft_exit_prog("Failed to initialize the linked list.\n", FG_RED, 0);
	list->key = get_env_key(env_line, &end_key);
	list->value = get_env_value(env_line, &end_key);
	list->next = NULL;
	return (list);
}

t_lst	*add_elem(t_lst *list, t_d *d, char *env_line)
{
	if (!list)
	{
		list = lst_new(d, env_line);
		return (list);
	}
	list->next = lst_new(d, env_line);
	return (list->next);
}


t_lst   *env_to_list(char **env, t_d *d, int i, t_lst *list)
{
	t_lst	*tmp;

	tmp = NULL;
	while (env[i])
	{
		list = add_elem(list, d, env[i]);
		if (i == 0)
			tmp = list;
		i++;
	}
	return (tmp);
}



int		main(int ac, char **av, char **env)
{
	char	buf[1];
	char	*buff;
	pid_t		father;
	char	*gnl_buff;
	t_lst	*list;
	t_d		d;
	char	**arg;
	char *foo[] = { "/bin/ls", "-l", NULL };
	//	printf("av[0] = %s\n", av[1]);
	//	av[0] = "/bin/ls";	
	//	ft_color_style(BG_LBLUE, NULL, "\n", 1);
	//	execve("/usr/bin/env", NULL, env);
	list = env_to_list(env, &d, 0, NULL);
	while (list)
	{
		printf("key = \"%s\" / value = \"%s\"\n", list->key, list->value);
		list = list->next;
	}
	while (1)
	{
		print_bash();
		get_next_line(0, &gnl_buff);
		printf("gnl_buff = %s\n", gnl_buff);
		if (strcmp(gnl_buff, "exit") == 0)
			exit(0);
		arg = transform_str(gnl_buff, &d, 0, 0);
		arg[0] = ft_strdup("minishell");
		print_tab(arg);
		father = fork();
		if (father == 0)
		{
			free_arg(arg);
		}
		if (father > 0)
			kill(father, SIGKILL);
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
