/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 10:16:22 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/09 09:51:38 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		nb_base_len(unsigned long long int nb, int size_base)
{
	double	i;
	int		len;

	i = 1;
	len = 1;
	while (i < nb)
	{
		len++;
		i = i * size_base;
	}
	return (len);
}

void	put_base(unsigned long long int nb, char *str, char *base)
{
	unsigned int	size_base;
	int				i;

	size_base = ft_strlen(base);
	if (nb >= size_base)
		put_base(nb / size_base, str, base);
	i = ft_strlen(str);
	str[i] = base[nb % size_base];
}

int		ldb_base_len(long double nb, int size_base)
{
	long double	i;
	int			len;

	i = 1;
	len = 1;
	while (i < nb)
	{
		len++;
		i = i * size_base;
	}
	return (len);
}

void	put_dbl(long double nb, char *str, t_flag flags)
{
	int	i;

	i = 0;
	while (i < flags.pre)
	{
		nb -= (unsigned long long int)nb;
		nb *= 10.0;
		str[i++] = '0' + ((unsigned long long int)nb % 10);
	}
}
