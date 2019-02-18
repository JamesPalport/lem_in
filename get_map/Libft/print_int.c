/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:00:32 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/09 11:12:40 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_di(t_flag flags, va_list ap)
{
	long long int	nbr;
	char			*tmp1;
	char			*tmp2;
	int				len;

	if (flags.conv == 'D')
		cap_conv(&flags);
	nbr = va_arg(ap, long long int);
	adj_size(&nbr, flags);
	if (!nbr && flags.pre == 0)
		tmp1 = ft_strnew(0);
	else if (!(tmp1 = lli_str(nbr, flags)))
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
