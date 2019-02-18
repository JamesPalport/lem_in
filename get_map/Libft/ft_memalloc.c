/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 12:25:09 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/13 14:58:07 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	i;
	void	*out;

	if ((out = (void *)malloc(sizeof(void) * size)) == 0)
		return (NULL);
	i = 0;
	while (i < size)
		*(int *)(out + i++) = 0;
	return (out);
}
