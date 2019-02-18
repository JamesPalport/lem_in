/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 10:31:22 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/09 11:01:52 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_padd_char(char *padd, t_flag flags)
{
	padd[1] = '\0';
	padd[0] = ' ';
	if (flags.pad == '0' && (flags.conv == 'f' || flags.pre == -1
				|| (flags.pre == 0
				&& ((flags.conv == 'c' || flags.conv == 's') || flags.err))))
		padd[0] = '0';
}

void	alt_dup(char **base, char *str)
{
	if (*base)
		free(*base);
	*base = ft_strdup(str);
}

void	set_base(t_flag *flags, char **base, char *str)
{
	int	len;

	len = ft_strlen(str);
	if (flags->conv == 'X' && ft_strlen(str) != 0)
		alt_dup(base, "0X");
	else if ((flags->conv == 'x' && ft_strlen(str) != 0) || flags->conv == 'p')
		alt_dup(base, "0x");
	else if (flags->conv != 'x' && flags->conv != 'X')
		alt_dup(base, "0");
	else
		alt_dup(base, "");
	if (flags->conv != 'p'
			&& (ft_strlen(str) == 1 && str[0] == '0'))
		alt_dup(base, "");
	if (flags->min_len == -1 || flags->min_len <= len)
		flags->min_len = len + ft_strlen(*base);
}
