/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 16:32:46 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/02 12:41:17 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				get_int(va_list ap)
{
	int	nbr;

	nbr = (int)va_arg(ap, int);
	return (nbr);
}

long int		get_lint(va_list ap)
{
	long int	nbr;

	nbr = (long int)va_arg(ap, long int);
	return (nbr);
}

long long int	get_llint(va_list ap)
{
	long long int	nbr;

	nbr = (long long int)va_arg(ap, long long int);
	return (nbr);
}

short int		get_sint(va_list ap)
{
	short int	nbr;

	nbr = (short int)va_arg(ap, int);
	return (nbr);
}

char			get_ssint(va_list ap)
{
	char	nbr;

	nbr = (char)va_arg(ap, int);
	return (nbr);
}
