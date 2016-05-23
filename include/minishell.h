/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 17:18:58 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/19 19:16:35 by vsteffen         ###   ########.fr       */
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

typedef struct			s_lst
{
//	char				*name;
	//char				*path;
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
}						t_d;

typedef void (*t_handler)(int);

t_handler				signal(int sig, t_handler func);

void ft_env(t_lst *list);

#endif
