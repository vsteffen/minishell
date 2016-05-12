/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 17:18:58 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/12 18:04:37 by vsteffen         ###   ########.fr       */
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

typedef struct			s_list_ls
{
	char				*name;
	char				*path;
	struct s_list_ls	*next;
}						t_list_ls;

typedef struct			s_d
{
	char				*name;
	char				*path;
}						t_d;

typedef void (*t_handler)(int);

int						main(int ac, char **av);

t_handler				signal(int sig, t_handler func);

#endif
