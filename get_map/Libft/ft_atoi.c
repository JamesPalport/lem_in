/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:47:03 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/13 16:02:53 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_signe(const char *str, int *signe)
{
	int	i;

	i = 0;
	*signe = 1;
	while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
				|| str[i] == '\f' || str[i] == '\r'
				|| str[i] == '\v') && str[i])
		i++;
	if (str[i] == '-')
	{
		*signe = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (i);
}

int			ft_atoi(const char *str)
{
	int			i;
	int			signe;
	long int	nbr;

	signe = 0;
	i = ft_signe(str, &signe);
	nbr = 0;
	while (str[i] && ((str[i] >= '0') && (str[i] <= '9')))
	{
		nbr *= 10;
		nbr += str[i] - '0';
		i++;
	}
	return (nbr * signe);
}
