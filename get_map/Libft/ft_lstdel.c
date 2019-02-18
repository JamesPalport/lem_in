/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 12:51:31 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/14 13:04:57 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next;
	t_list	*cur;

	if (alst && del)
	{
		cur = *alst;
		while (cur)
		{
			next = cur->next;
			del(cur->content, cur->content_size);
			free(cur);
			cur = next;
		}
		*alst = NULL;
	}
}
