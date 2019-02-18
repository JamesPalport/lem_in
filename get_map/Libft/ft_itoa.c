/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 09:37:53 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/14 11:11:09 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nblen(long int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	if (n == 0)
		return (2);
	while (n)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static void	writenb(long int n, char *str, int i)
{
	if (n > 9)
	{
		writenb(n / 10, str, i);
		writenb(n % 10, str, i + nblen(n) - 2);
	}
	if (n < 10)
		str[i + nblen(n) - 2] = '0' + n;
}

char		*ft_itoa(int n)
{
	int			len;
	char		*out;
	int			i;
	long int	nb;

	nb = n;
	len = nblen(nb);
	if ((out = (char *)malloc(sizeof(char) * len)) == 0)
		return (NULL);
	i = 0;
	if (nb < 0)
	{
		out[i++] = '-';
		nb *= -1;
	}
	writenb(nb, out, i);
	out[len - 1] = '\0';
	return (out);
}
