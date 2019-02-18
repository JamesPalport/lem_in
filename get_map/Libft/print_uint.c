/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 13:03:27 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/09 11:16:30 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex(t_flag flags, va_list ap)
{
	long long unsigned int	nbr;
	char					*tmp1;
	char					*tmp2;
	int						len;

	nbr = va_arg(ap, unsigned long long int);
	adj_uns_size(&nbr, flags);
	if (!nbr && !flags.pre)
	{
		if ((tmp1 = ft_strnew(0)) == NULL)
			return (-1);
	}
	else if (!(tmp1 = ui_long_hex(nbr, (flags.conv == 'X'))))
		return (-1);
	if (!(tmp1 = pre_hex(tmp1, flags)))
		return (-1);
	if (!(tmp2 = padd_hex(tmp1, flags)))
		return (lib_diff(tmp2, tmp1, tmp2));
	ft_putstr_fd(tmp2, flags.fd);
	len = ft_strlen(tmp2);
	lib_diff(NULL, tmp1, tmp2);
	return (len);
}

int	print_o(t_flag flags, va_list ap)
{
	long long unsigned int	nbr;
	char					*tmp1;
	char					*tmp2;
	int						len;

	if (flags.conv == 'O')
		cap_conv(&flags);
	nbr = va_arg(ap, unsigned long long int);
	adj_uns_size(&nbr, flags);
	if (!(tmp1 = ui_long_oct(nbr, flags)))
		return (-1);
	if (flags.pre > (int)ft_strlen(tmp1))
		flags.alt = 0;
	if (!(tmp1 = pre_hex(tmp1, flags)))
		return (-1);
	if (!(tmp2 = padd_hex(tmp1, flags)))
		return (lib_diff(tmp2, tmp1, tmp2));
	ft_putstr_fd(tmp2, flags.fd);
	len = ft_strlen(tmp2);
	lib_diff(NULL, tmp1, tmp2);
	return (len);
}

int	print_u(t_flag flags, va_list ap)
{
	unsigned long long int	nbr;
	char					*tmp1;
	char					*tmp2;
	int						len;

	if (flags.conv == 'U')
		cap_conv(&flags);
	nbr = va_arg(ap, unsigned long long int);
	adj_uns_size(&nbr, flags);
	if (!nbr && !flags.pre)
	{
		if ((tmp1 = ft_strnew(0)) == NULL)
			return (-1);
	}
	else if (!(tmp1 = ulli_str(nbr)))
		return (-1);
	if (!(tmp1 = pre_hex(tmp1, flags)))
		return (-1);
	if (!(tmp2 = padd_str(tmp1, flags)))
		return (lib_diff(tmp2, tmp1, tmp2));
	ft_putstr_fd(tmp2, flags.fd);
	len = ft_strlen(tmp2);
	lib_diff(NULL, tmp1, tmp2);
	return (len);
}
