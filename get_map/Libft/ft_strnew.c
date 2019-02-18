/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 12:45:37 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/11 12:50:40 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*out;
	size_t	i;

	if ((out = (char *)malloc(sizeof(char) * (size + 1))) == 0)
		return (NULL);
	i = 0;
	while (i <= size)
		out[i++] = '\0';
	return (out);
}
