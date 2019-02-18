/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 13:06:22 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/13 15:07:28 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*out;
	int		i;

	if (s)
	{
		if ((out = ft_strnew(ft_strlen(s))) == NULL)
			return (NULL);
		i = 0;
		while (s[i])
		{
			out[i] = f(s[i]);
			i++;
		}
		return (out);
	}
	return (NULL);
}
