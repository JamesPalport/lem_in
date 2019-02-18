/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:13:29 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/13 12:02:07 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		init;

	i = 0;
	init = 0;
	while (s1[init])
		init++;
	while ((s2[i]) && (i < n))
	{
		s1[init + i] = s2[i];
		i++;
	}
	s1[init + i] = '\0';
	return (s1);
}
