/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:51:32 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/11 12:13:17 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	i;
	size_t	j;

	if (small[0] == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && (i < len))
	{
		j = 0;
		while ((big[i + j] == small[j]) && small[j] && (i + j < len))
			j++;
		if (small[j] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
