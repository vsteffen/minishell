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

char		**transform_str(t_d *d, int pos, int deb)
{
	char	**arg_prog;

	if (!(arg_prog = (char**)malloc(sizeof(char*) * (nb_param(d->gnl_buff) + 1))))
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
	if (!value && !key)
		list->value = get_env_value(env_line, &end_key);
	else
		list->value = value;
	if (!key)
		d->env_end = list;
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

int		key_exist(t_lst *list, char *key, char *value)
{
	while (list)
	{
		if (ft_strequ(key, list->key))
		{
			free(key);
			free(list->value);
			list->value = value;
			return (1);
		}
		list = list->next;
	}
	return (0);
}

void ft_add_env(t_d *d, char *key, char *value)
{
	t_lst		*list;

	list = d->env_end;
	list->next = lst_new(d, NULL, key, value);
	d->env_end = list->next;
}

void 	ft_setenv(t_d *d)
{
	int	arg;
	char *ptr;
	char *key;
	char *value;

	arg = 1;
	while (d->buff[arg] != '\0')
	{
		ptr = ft_strchr(d->buff[arg], '=');
		if (ptr == NULL || d->buff[arg][0] == '=')
		{
			ft_superstr("Invalid key or value for \"", d->buff[arg], "\"\nUsage: setenv key=value\n", NULL);
			arg++;
			continue ;
		}
		key = ft_strsub(d->buff[arg], 0, ptr - d->buff[arg]);
		value = ft_strdup(ptr + 1);
		if (key_exist(d->lst_env, key, value))
		{
			arg++;
			continue ;
		}
		else
			ft_add_env(d, key, value);
		arg++;
	}
}

void ft_env(t_lst *list)
{
	while (list)
	{
		ft_superstr(list->key, "=", list->value, "\n");
		//printf("key = \"%s\" / value = \"%s\"\n", list->key, list->value);
		list = list->next;
	}
}

int		unsetenv_check_lst(t_lst *list, t_d *d, char *key, int *arg)
{
	t_lst *after;

	while (list->next)
	{
		if (list->next)
		{
			if (ft_strequ(key, list->next->key))
			{
				free(list->next->key);
				free(list->next->value);
				after = list->next->next;
				free(list->next);
				list->next = after;
				if (list->next == NULL)
					d->env_end = list; // SI IL S AGIT DU DERNIER MAILLON DE SUPPRIMER
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

void ft_unsetenv(t_lst *list, t_d *d)
{
	t_lst		*tmp;
	int			arg;

	tmp = list;
	arg = 1;
//	printf("BEFORE WHILE d->buff[arg] = %s\n", d->buff[arg]);
	while (d->buff[arg] != '\0' && list)
	{
		list = tmp;
		if (ft_strequ(tmp->key, d->buff[arg]))
		{
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
			arg++;
		}
	}
}

int		main(int ac, char **av, char **env)
{
	char	buf[1];
	char	*buff;
	pid_t		father;
	t_lst	*list;
	t_d		d;
	char	**arg;
	char *foo[] = { "/bin/ls", "-l", NULL };
	//	printf("av[0] = %s\n", av[1]);
	//	av[0] = "/bin/ls";
	//	ft_color_style(BG_LBLUE, NULL, "\n", 1);
	//	execve("/usr/bin/env", NULL, env);

//	struct_ini(t-d *d); --> env_end = NULL;
	d.lst_env = env_to_list(env, &d, 0, NULL);
	//ft_env(d.lst_env);
	while (1)
	{
		print_bash();
		get_next_line(0, &(d.gnl_buff));
		if (ft_strequ(d.buff[0], "exit"))
			exit(0);
		d.buff = transform_str(&d, 0, 0);
		//d.buff[0] = ft_strdup("minishell");
		//print_tab(d.buff);
		if (ft_strequ(d.buff[0], "setenv"))
			ft_setenv(&d);
		if (ft_strequ(d.buff[0], "env"))
			ft_env(d.lst_env);
		if (ft_strequ(d.buff[0], "unsetenv"))
			ft_unsetenv(d.lst_env, &d);
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
