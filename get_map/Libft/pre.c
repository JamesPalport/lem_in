/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 09:41:28 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/02 14:23:02 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*pre_str(char *str, t_flag flags)
{
	char	*out;
	int		i;

	i = 0;
	if (flags.pre == -1)
		return (str);
	if ((out = ft_strnew(flags.pre + 1)) == NULL)
		return (NULL);
	while (i < flags.pre)
	{
		out[i] = str[i];
		i++;
	}
	out[flags.pre] = '\0';
	return (out);
}

char	*pre_hex(char *str, t_flag flags)
{
	char	*out;
	int		i;
	int		len;

	len = ft_strlen(str);
	if (str[0] == ' ' || str[0] == '+' || str[0] == '-')
		flags.pre++;
	i = 0;
	if (flags.pre == -1 || flags.pre <= len)
		return (str);
	if ((out = ft_strnew(flags.pre + 1)) == NULL)
		return (NULL);
	while (i < flags.pre - len)
		out[i++] = '0';
	if (str[0] == ' ' || str[0] == '+' || str[0] == '-')
	{
		out[i] = '0';
		out[0] = str[0];
		ft_strlcat(out, str + 1, flags.pre + 1);
	}
	else
		ft_strlcat(out, str, flags.pre + 1);
	free(str);
	out[flags.pre] = '\0';
	return (out);
}
