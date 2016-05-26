/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:08:07 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/24 15:08:11 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
t_list_ls	*list_dir(t_list_ls *list, t_d *d, char *path, t_list_ls *lst_deb)
{
	DIR				*dir_s;
	struct dirent	*dir_file;

  *dir_s = NULL;
	*dir_file = NULL;
	list_dir4(&dir_s, &dir_file, &no_null);
	if ((dir_s = opendir(path)) == NULL)
		return (list_dir2(d, path));
   while (dir_file = readdir(dir_s)) != NULL)
		}
    if (closedir(dir_s) == -1)
  		ft_exit_prog("Fail to close directory stream\n", FG_RED, 0);
	}
	list_dir5(dir_s);
	choose_sort_master(&lst_deb, d);
	return (lst_deb);
}
*/



int ft_cd(t_d *d)
{
  t_lst *list;
  char *dest;
  char *old;
  char *buff;
  char *tmp;
  size_t size;


  list = d->lst_env;
  dest = NULL;
  if (!d->buff[1])
  {
    while (list)
    {
      if (ft_strequ("HOME", list->key))
      {
        dest = list->value;
        list = NULL;
        continue ;
      }
      list = list->next;
    }
    if (dest == NULL)
    {
      ft_putstr("cd: HOME not set\n");
      d->cmd_status = 0;
      return (1);
    }
  }
  else if (ft_strequ(d->buff[1], "-"))
  {
    while (list)
    {
      if (ft_strequ("OLDPWD", list->key))
      {
          dest = list->value;
          list = NULL;
          continue ;
      }
      list = list->next;
    }
    if (dest == NULL)
    {
      ft_putstr("cd: OLDPWD not set\n");
      d->cmd_status = 0;
      return (1);
    }
  }
  else
    dest = d->buff[1];
  if (!(old = (char *)malloc(sizeof(size))))
    ft_exit_prog("Fail to malloc buff for old path\n", FG_RED, 0);
  old = getcwd(NULL, 255);
  if (chdir(dest) == -1)
  {
    d->cmd_status = 0;
    ft_superstr("cd: ", dest,": no such directory or permission denied\n", NULL);
    return (1);
  }
  dest = getcwd(NULL, 255);
  list = d->lst_env;
  while (list)
  {

    if (ft_strequ("OLDPWD", list->key))
    {
      free(list->value);
      list->value = old;
    }
    if (ft_strequ("PWD", list->key))
    {
      free(list->value);
      list->value = dest;
    }
    list = list->next;
  }
  return (1);
}
