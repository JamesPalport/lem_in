/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:37:16 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/11 12:15:09 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *small)
{
	int	i;
	int	j;

	i = 0;
	if (small[0] == '\0')
		return ((char *)big);
	while (big[i])
	{
		j = 0;
		while ((big[i + j] == small[j]) && (small[j]))
			j++;
		if (small[j] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
