/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_padd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 09:59:51 by amerrouc          #+#    #+#             */
/*   Updated: 2019/02/07 14:52:40 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	apply_padd_str(char *out, const char *str, char *padd, t_flag flags)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	if (flags.pad == 0 || flags.pad == '0')
	{
		while (i++ < flags.min_len - len)
			ft_strlcat(out, padd, flags.min_len + 1);
		ft_strlcat(out, str, flags.min_len + 1);
	}
	else
	{
		ft_strcat(out, str);
		while (i++ < flags.min_len - len)
			ft_strlcat(out, padd, flags.min_len + 1);
	}
	if (!ft_isdigit(str[0]) && (flags.conv == 'd' || flags.conv == 'D'
			|| flags.conv == 'i' || flags.conv == 'f') && !ft_strcmp("0", padd))
	{
		out[0] = str[0];
		out[i - 1] = '0';
	}
}

char	*padd_1(char *str, char *padd, char *base, t_flag flags)
{
	char	*out;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	if ((out = ft_strnew(flags.min_len + 1)) == NULL)
		return (NULL);
	if ((flags.conv == 'p' || flags.alt == 1) && padd[0] == '0')
		ft_strcat(out, base);
	if (flags.alt == 1 || flags.conv == 'p')
		flags.min_len -= ft_strlen(base);
	while (i++ < flags.min_len - len)
		ft_strcat(out, padd);
	if (padd[0] != '0' && (flags.conv == 'p' || flags.alt == 1))
		ft_strcat(out, base);
	ft_strcat(out, str);
	return (out);
}

char	*padd_2(char *str, char *padd, char *base, t_flag flags)
{
	char	*out;
	int		i;
	int		len;

	if ((out = ft_strnew(flags.min_len + 1)) == NULL)
		return (NULL);
	len = ft_strlen(str);
	i = 0;
	if (flags.conv == 'p' || flags.alt == 1)
		ft_strcat(out, base);
	ft_strcat(out, str);
	if (flags.alt == 1 || flags.conv == 'p')
		flags.min_len -= ft_strlen(base);
	while (i++ < flags.min_len - len)
		ft_strcat(out, padd);
	return (out);
}

char	*apply_padd_hex(char *str, char *padd, char *base, t_flag flags)
{
	char	*out;

	if (flags.pad == 0 || flags.pad == '0')
		out = padd_1(str, padd, base, flags);
	else
		out = padd_2(str, padd, base, flags);
	return (out);
}
