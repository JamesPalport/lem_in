/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:54:46 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/13 13:48:31 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	dstlen = ft_strlen(dst);
	if (dstlen > size)
		dstlen = size;
	srclen = ft_strlen(src);
	if (dstlen == size)
		return (size + srclen);
	i = 0;
	while ((src[i]) && ((dstlen + i) < (size - 1)))
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	if ((dstlen + i) < (size))
		dst[dstlen + i] = '\0';
	else
		dst[dstlen + size - 1] = '\0';
	return (dstlen + srclen);
}
