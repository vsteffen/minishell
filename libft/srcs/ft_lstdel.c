/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <vsteffen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/22 21:07:49 by vsteffen          #+#    #+#             */
/*   Updated: 2015/12/23 00:21:29 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*list;
	t_list		*next_lst;

	if (!alst || !del)
		return ;
	list = *alst;
	while (list)
	{
		next_lst = list->next;
		ft_lstdelone(&list, del);
		list = next_lst;
	}
	*alst = NULL;
}
