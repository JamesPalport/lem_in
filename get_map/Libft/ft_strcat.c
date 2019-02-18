/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:06:09 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/09 12:13:20 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int	i;
	int	init;

	i = 0;
	init = 0;
	while (s1[init])
		init++;
	while (s2[i])
	{
		s1[init + i] = s2[i];
		i++;
	}
	s1[init + i] = '\0';
	return (s1);
}
