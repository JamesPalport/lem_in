/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 13:54:17 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/13 15:17:19 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;

	if (s1 && s2)
	{
		if ((out = ft_strnew(ft_strlen(s1) + ft_strlen(s2))) == NULL)
			return (NULL);
		out = ft_strcat(out, s1);
		out = ft_strcat(out, s2);
		return (out);
	}
	return (NULL);
}
