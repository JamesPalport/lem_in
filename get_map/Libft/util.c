/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 11:49:12 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/09 12:56:48 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		lib_diff(char *str, char *tmp1, char *tmp2)
{
	if (tmp1 == tmp2)
	{
		if (tmp1 != str)
			free(tmp1);
	}
	else
	{
		if (tmp1 != str)
			free(tmp1);
		if (tmp2 != str)
			free(tmp2);
	}
	return (-1);
}

int		len_flags(char *str, t_flag *flags)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != flags->conv)
		i++;
	if (!str[i])
		i--;
	return (i + 1);
}

void	cap_conv(t_flag *flags)
{
	flags->mod[0] = 'l';
	flags->mod[1] = '\0';
}
