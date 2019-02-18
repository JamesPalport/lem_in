/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:46:31 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/14 14:55:40 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	test_sqrt(int nbr, long int i, int *ptr)
{
	if ((i * i) < nbr)
		test_sqrt(nbr, i + 1, ptr);
	else
	{
		if ((i * i) == nbr)
			*ptr = i;
	}
}

int			ft_sqrt(int nb)
{
	int i;

	i = 0;
	if (nb <= 0)
		return (0);
	if (nb == 2)
		return (0);
	test_sqrt(nb, i, &i);
	if ((i * i) == nb)
		return (i);
	return (0);
}
