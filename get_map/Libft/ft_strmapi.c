/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 13:13:57 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/13 15:07:58 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*out;
	unsigned int	i;

	if (s)
	{
		if ((out = ft_strnew(ft_strlen(s))) == NULL)
			return (NULL);
		i = 0;
		while (s[i])
		{
			out[i] = f(i, s[i]);
			i++;
		}
		return (out);
	}
	return (NULL);
}
