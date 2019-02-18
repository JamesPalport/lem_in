/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chs_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 10:52:00 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/07 16:04:16 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				chose_fct(t_flag *flags)
{
	char	c;

	c = flags->conv;
	if (c == 'c')
		return (0);
	if (c == 's')
		return (1);
	if (c == 'p')
		return (2);
	if (c == 'd' || c == 'i' || c == 'D')
		return (3);
	if (c == 'o' || c == 'O')
		return (4);
	if (c == 'u' || c == 'U')
		return (5);
	if (c == 'x' || c == 'X')
		return (6);
	if (c == 'f' || c == 'F')
		return (7);
	return (8);
}

void			adj_size(long long int *nbr, t_flag flags)
{
	if (!ft_strcmp("ll", flags.mod))
		return ;
	else if (!ft_strcmp("l", flags.mod))
		*nbr = (long int)*nbr;
	else if (!ft_strcmp("h", flags.mod))
		*nbr = (short int)*nbr;
	else if (!ft_strcmp("hh", flags.mod))
		*nbr = (char)*nbr;
	else
		*nbr = (int)*nbr;
}

void			adj_uns_size(unsigned long long int *nbr, t_flag flags)
{
	if (!ft_strcmp("ll", flags.mod))
		return ;
	else if (!ft_strcmp("l", flags.mod))
		*nbr = (unsigned long int)*nbr;
	else if (!ft_strcmp("h", flags.mod))
		*nbr = (unsigned short int)*nbr;
	else if (!ft_strcmp("hh", flags.mod))
		*nbr = (unsigned char)*nbr;
	else
		*nbr = (unsigned int)*nbr;
}

void			adj_prec(long double *nbr, t_flag *flags)
{
	long double	tmp;
	long double	dec;
	double		pow;
	int			i;
	double		sign;

	i = 0;
	pow = 1.0;
	sign = (*nbr >= 0) ? 1.0 : -1.0;
	if (flags->pre == -1)
		flags->pre = 6;
	while (i++ < flags->pre)
		pow *= 10;
	tmp = (*nbr >= 0) ? *nbr : -*nbr;
	tmp -= (unsigned long long int)tmp;
	dec = (tmp * pow) - (unsigned long long int)(tmp * pow);
	dec -= (unsigned long long int)dec;
	if (dec >= 0.5)
		*nbr += sign / (pow);
}
