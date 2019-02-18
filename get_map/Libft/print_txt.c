/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_txt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 09:56:22 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/09 11:15:45 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(t_flag flags, va_list ap)
{
	char	c;
	int		len;
	char	padd[2];

	c = (char)va_arg(ap, int);
	len = 0;
	set_padd_char(padd, flags);
	if (flags.pad == 0 || flags.pad == '0')
	{
		while (len++ < flags.min_len - 1)
			ft_putchar_fd(padd[0], flags.fd);
		ft_putchar_fd(c, flags.fd);
	}
	else
	{
		ft_putchar_fd(c, flags.fd);
		while (len++ < flags.min_len - 1)
			ft_putchar_fd(padd[0], flags.fd);
	}
	return (len);
}

int	print_s(t_flag flags, va_list ap)
{
	char	*str;
	char	*tmp1;
	char	*tmp2;
	int		len;

	str = va_arg(ap, char *);
	tmp1 = str;
	tmp2 = str;
	if (!str)
		str = "(null)";
	if (!(tmp1 = pre_str(str, flags)))
		return (-1);
	if (!(tmp2 = padd_str(tmp1, flags)))
		return (lib_diff(str, tmp1, tmp2));
	ft_putstr_fd(tmp2, flags.fd);
	len = ft_strlen(tmp2);
	lib_diff(str, tmp1, tmp2);
	return (len);
}

int	print_p(t_flag flags, va_list ap)
{
	char	*str;
	char	*tmp1;
	char	*tmp2;
	int		len;

	str = va_arg(ap, char *);
	if (!str && !flags.pre)
	{
		if ((tmp1 = ft_strnew(0)) == NULL)
			return (-1);
	}
	else if (!(tmp1 = ui_long_hex((long int)str, 0)))
		return (-1);
	if (!(tmp1 = pre_hex(tmp1, flags)))
		return (-1);
	if (!(tmp2 = padd_hex(tmp1, flags)))
		return (lib_diff(str, tmp1, tmp2));
	ft_putstr_fd(tmp2, flags.fd);
	len = ft_strlen(tmp2);
	lib_diff(str, tmp1, tmp2);
	return (len);
}
