/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_style.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 16:14:08 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/19 16:24:35 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_color_style(char *color, char *str)
{
	ft_putstr(color);
	if (str == NULL)
		return ;
	ft_putstr(str);
	ft_putstr("\033[0m");
}
