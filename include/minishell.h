/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 17:18:58 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/27 17:04:03 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <math.h>
# include <time.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>
# include <signal.h>
# include "../libft/include/libft.h"

typedef struct stat	t_stat;

typedef struct			s_lst
{
	char				*key;
	char				*value;
	struct s_lst		*next;
}						t_lst;

typedef struct			s_d
{
	char				*name;
	char				*path;
	t_lst				*lst_env;
	t_lst				*env_end;
	int					nb_arg;
	char				*gnl_buff;
	char				**buff;
	char				*pwd;
	size_t				pwd_size;
	char				*oldpwd;
	char				*shlvl;
	char				*home;
	char				*shell;
	char				**exec;
	char				**new_env;
	int					cmd_status;
}						t_d;

typedef void			(*t_handler)(int);

t_handler				signal(int sig, t_handler func);

void					print_tab(char **tab);

int						key_exist(t_lst *list, char *key, char *value, t_d *d);
void					ft_add_env(t_d *d, char *key, char *value);
int						ft_setenv(t_d *d, int arg);

char					*ft_envjoin(char const *s1, char const *s2);
t_lst					*env_to_list(char **env, t_d *d, int i, t_lst *list);
int						if_no_arg(t_d *d, char *first_arg, int status);
int						ft_env(t_lst *list);

void					get_key_important(t_d *d, char *key, char *value);
void					reset_key_important(t_d *d, char *key);
t_lst					*lst_new(t_d *d, char *env_line, char *key,
	char *value);
t_lst					*add_elem(t_lst *list, t_d *d, char *env_line);

char					*get_env_key(char *env_line, int *end_key);
char					*get_env_value(char *env_line, int *end_key);
void					get_exec_tab(t_d *d, char *value);
void					reset_exec_tab(t_d *d, char *value, int status);

int						unsetenv_check_lst(t_lst *list, t_d *d, char *key,
	int *arg);
int						ft_unsetenv(t_d *d, int arg);

int						ft_cd(t_d *d);

void					env_to_char(t_d *d, int i, int tmp);
int						try_execve(t_d *d);
int						launch_execve(t_d *d, pid_t father);

void					print_bash(t_d *d);
int						nb_param(char *gnl_buff);
char					**transform_str(t_d *d, int pos, int deb);

#endif
