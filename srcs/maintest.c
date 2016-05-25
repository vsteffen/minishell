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

void print_bash(t_d *d)
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
	free(arg[i]);
	free(arg);
	i = 0;
}

void struct_ini(t_d *d)
{
	d->env_end = NULL;
	d->pwd = NULL;
	d->oldpwd = NULL;
	d->shlvl = NULL;
	d->home = NULL;
	d->shell = NULL;
	d->exec = malloc(sizeof(d->exec)); //--> don't forget at the end to free him
	d->exec[0] = NULL;
	d->new_env = malloc(sizeof(d->new_env));
	d->new_env[0] = NULL;
	d->cmd_status = 1;
}

int 	ft_isbuiltin(t_d *d)
{
	if (ft_strequ(d->buff[0], "exit"))
	{
		free_arg(d->buff); // and all shit allocated
		exit(0);
	}
	if (ft_strequ(d->buff[0], "setenv"))
		return (ft_setenv(d));
	if (ft_strequ(d->buff[0], "env"))
		return (ft_env(d->lst_env));
	if (ft_strequ(d->buff[0], "unsetenv"))
		return (ft_unsetenv(d));
	if (ft_strequ(d->buff[0], "cd"))
		return (ft_cd(d));
	return (0);
}

void ft_add_pwd(t_d *d, int oldpwd_defined, int pwd_defined)
{
	t_lst		*list;

	if (!d->lst_env)
	{
		if (pwd_defined)
			list = lst_new(d, NULL, "PWD", d->pwd);
		else if (oldpwd_defined)
			list = lst_new(d, NULL, "OLDPWD", d->pwd);
		d->lst_env = list;
		d->env_end = list;
	}
	else
	{
		list = d->env_end;
		if (pwd_defined)
			list = lst_new(d, NULL, "PWD", d->pwd);
		else if (oldpwd_defined)
			list = lst_new(d, NULL, "OLDPWD", d->pwd);
		d->env_end = list->next;
	}
}
/*
void get_flocation(t_d *d)
{
	t_lst	*list;
	int		oldpwd_defined;
	int		pwd_defined;

	getcwd(d->pwd, d->pwd_size);
	list = d->lst_env;
	oldpwd_defined = 1;
	pwd_defined = 1;
	while (list && pwd_defined && oldpwd_defined)
	{
		if (ft_strequ(list->value, "PWD"))
		{
			list->value = d->pwd;
			pwd_defined = 0;
		}
//		if (ft_strequ(list
		list = list->next;
	}
	if (oldpwd_defined || pwd_defined)
		ft_add_pwd(d, pwd_defined, oldpwd_defined);
}

static t_list	*ft_lstdict(t_list *lst, const int n)
{
	while (lst)
	{
		if (lst->content_size == (size_t)n)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

static	char	*handle_first_buff(t_list *prec)
{
	int		i;
	char	*ret;

	i = 0;
	if (!prec->content)
		return (NULL);
	while (((char*)prec->content)[i] != '\n' &&
			((char*)prec->content)[i] != '\0')
		i++;
	if (((char*)prec->content)[i] == '\n')
	{
		if (i == 0)
		{
			ret = ft_strdup((char*)prec->content + 1);
			prec->content = (void*)ft_strdup(ret);
			ret = ft_memalloc(1);
		}
		else
		{
			ret = ft_strsub((char*)prec->content, 0, i);
			prec->content = (void*)((char*)prec->content + i + 1);
		}
		return (ret);
	}
	return (NULL);
}

static int		handle_buffer(t_list *prec, char **ret, int fd, int *r)
{
	int		i;
	char	buff[BUFF_SIZE + 1];

	i = -1;
	while ((*r = read(fd, buff, BUFF_SIZE)) && *r != -1)
	{
		i = 0;
		buff[*r] = '\0';
		while (buff[i] != '\0')
		{
			if (buff[i] == '\n')
			{
				buff[i] = '\0';
				*ret = ft_strjoin(*ret, buff);
				prec->content = (void*)ft_strdup(buff + i + 1);
				return (1);
			}
			i++;
		}
		*ret = ft_strjoin(*ret, buff);
	}
	if (i == -1 || *r == -1)
		return (-1);
	return (0);
}

static	char	*read_one_line(t_list *prec, int const fd, int *r)
{
	int		i;
	char	*ret;

	if ((ret = handle_first_buff(prec)))
		return (ret);
	ret = ft_strjoin("", (char*)prec->content);
	i = handle_buffer(prec, &ret, fd, r);
	if (*r == -1)
		return (NULL);
	if (i == 1)
		return (ret);
	if (i != -1)
	{
		prec->content = "";
		return (ret);
	}
	return (0);
}

int				get_next_line_jc(int const fd, char **line)
{
	static t_list	*list = NULL;
	t_list			*maillon;
	int				r;

	maillon = NULL;
	if (fd < 0 || !line)
		return (-1);
	if (list == NULL)
		list = ft_lstnew("", fd);
	maillon = ft_lstdict(list, fd);
	if (!maillon)
	{
		maillon = ft_lstnew("", fd);
		ft_lstadd(&list, maillon);
	}
	*line = read_one_line(maillon, fd, &r);
	if (r == -1)
		return (-1);
	if (*line == NULL)
		return (0);
	return (1);
}
*/

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
	struct_ini(&d);
	d.lst_env = env_to_list(env, &d, 0, NULL);
//	get_flocation(&d);
	//ft_env(d.lst_env);
	print_bash(&d);
	while (get_next_line(0, &(d.gnl_buff)))
	{
		d.buff = transform_str(&d, 0, 0);
		//d.buff[0] = ft_strdup("minishell");
		//print_tab(d.buff);
		if (ft_isbuiltin(&d))
		{
			//do some stuff
		}
		else if (try_execve(&d))
		{
			launch_execve(&d, father);
		}
		else
		{
			d.cmd_status = 0;
			ft_superstr("zsh: command not found: \"", d.buff[0], "\"\n", NULL);
		}
		free_arg(d.buff);
		print_bash(&d);
	}
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

}
*/
