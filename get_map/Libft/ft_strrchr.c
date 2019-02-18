/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:27:07 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/11 12:14:10 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	lp;

	if ((char)c == '\0')
		return ((char *)s + ft_strlen(s));
	i = 0;
	lp = -1;
	while (s[i])
	{
		if (s[i] == (char)c)
			lp = i;
		i++;
	}
	if (lp == -1)
		return (NULL);
	return ((char *)s + lp);
}
