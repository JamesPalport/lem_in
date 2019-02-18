/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 13:45:16 by amerrouc          #+#    #+#             */
/*   Updated: 2019/02/18 16:13:36 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*out;

	if (s)
	{
		if ((out = ft_strnew(len)) == NULL)
			return (NULL);
		ft_memcpy(out, s + start, len);
		return (out);
	}
	return (NULL);
}
