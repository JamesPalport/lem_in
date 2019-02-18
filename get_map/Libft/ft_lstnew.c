/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:38:37 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/14 15:21:50 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*out;

	if ((out = (t_list *)malloc(sizeof(t_list))) == 0)
		return (NULL);
	if (content == NULL)
	{
		out->content = NULL;
		out->content_size = 0;
	}
	else
	{
		if ((out->content = (void *)malloc(content_size)) == 0)
			return (NULL);
		ft_memcpy(out->content, content, content_size);
		out->content_size = content_size;
	}
	out->next = NULL;
	return (out);
}
