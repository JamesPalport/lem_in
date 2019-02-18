/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 09:03:07 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/09 11:01:22 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*padd_str(char const *str, t_flag flags)
{
	char	*out;
	int		len;
	char	padd[2];

	len = ft_strlen(str);
	if (flags.min_len == -1 || flags.min_len <= len)
		return ((char *)str);
	if ((out = ft_strnew(flags.min_len + 1)) == NULL)
		return (NULL);
	set_padd_char(padd, flags);
	apply_padd_str(out, str, padd, flags);
	return (out);
}

char	*padd_c(char c, t_flag flags)
{
	char	*out;
	int		len;
	char	padd[2];
	char	*str;

	if ((str = (char *)malloc(sizeof(char) * 2)) == NULL)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	len = 1;
	if (flags.min_len == -1 || flags.min_len <= 0)
		return ((char *)str);
	if ((out = ft_strnew(flags.min_len + 1)) == NULL)
		return (NULL);
	set_padd_char(padd, flags);
	apply_padd_str(out, str, padd, flags);
	return (out);
}

char	*padd_hex(char *str, t_flag flags)
{
	char	*out;
	int		len;
	char	padd[2];
	char	*base;

	base = NULL;
	len = ft_strlen(str);
	if ((flags.min_len == -1 || flags.min_len <= len)
			&& (flags.conv != 'p' && flags.alt != 1))
		return (str);
	set_padd_char(padd, flags);
	set_base(&flags, &base, str);
	out = apply_padd_hex(str, padd, base, flags);
	free(base);
	return (out);
}
