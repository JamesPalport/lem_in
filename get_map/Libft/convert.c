/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 10:45:53 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/07 16:22:12 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ui_long_hex(unsigned long long int nb, int b)
{
	char	*num;
	char	*base;

	if (b)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	num = ft_strnew(nb_base_len(nb, 16) + 1);
	put_base(nb, num, base);
	return (num);
}

char	*ui_long_oct(unsigned long long int nb, t_flag flags)
{
	char	*num;
	char	*base;

	if (!nb && !flags.pre)
		return (ft_strnew(0));
	base = "01234567";
	num = ft_strnew(nb_base_len(nb, 8) + 1);
	put_base(nb, num, base);
	return (num);
}

char	*lli_str(long long int nb, t_flag flags)
{
	char					*num;
	char					*base;
	unsigned long long int	nbr;
	int						len;

	base = "0123456789";
	nbr = (nb > 0) ? nb : -nb;
	len = nb_base_len(nbr, 10);
	num = ft_strnew(len + 1);
	if (nb < 0)
		num[0] = '-';
	else
	{
		if (flags.sign == 1)
			num[0] = ' ';
		else if (flags.sign == 2)
			num[0] = '+';
	}
	put_base(nbr, num, base);
	return (num);
}

char	*ulli_str(unsigned long long int nbr)
{
	char	*num;
	char	*base;
	int		len;

	base = "0123456789";
	len = nb_base_len(nbr, 10);
	num = ft_strnew(len + 1);
	put_base(nbr, num, base);
	return (num);
}

char	*ldb_str(long double nb, t_flag flags)
{
	char		*num;
	char		*base;
	long double	nbr;
	int			len;

	base = "0123456789";
	nbr = (nb > 0) ? nb : -nb;
	len = ldb_base_len(nbr, 10);
	num = ft_strnew(len + 2 + flags.pre);
	if (nb < 0)
		num[0] = '-';
	else
	{
		if (flags.sign == 1)
			num[0] = ' ';
		else if (flags.sign == 2)
			num[0] = '+';
	}
	put_base(nbr, num, "0123456789");
	if (flags.pre)
	{
		num[ft_strlen(num)] = '.';
		put_dbl(nbr, num + ft_strlen(num), flags);
	}
	return (num);
}
