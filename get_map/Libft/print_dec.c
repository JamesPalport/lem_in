/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 09:13:10 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/09 11:11:38 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_dec(t_flag flags, va_list ap)
{
	long double		nbr;
	char			*tmp1;
	char			*tmp2;
	int				len;

	if (!ft_strcmp("L", flags.mod))
		nbr = va_arg(ap, long double);
	else
		nbr = va_arg(ap, double);
	adj_prec(&nbr, &flags);
	if (!nbr && flags.pre == 0)
		tmp1 = ft_strnew(0);
	else if (!(tmp1 = ldb_str(nbr, flags)))
		return (-1);
	if (!(tmp2 = padd_str(tmp1, flags)))
		return (lib_diff(tmp2, tmp1, tmp2));
	ft_putstr_fd(tmp2, flags.fd);
	len = ft_strlen(tmp2);
	lib_diff(tmp1, tmp1, tmp2);
	return (len);
}
