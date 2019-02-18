/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dec_conb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 09:40:37 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/07 15:37:32 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*dec_str(long double nb, t_flag flags)
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
