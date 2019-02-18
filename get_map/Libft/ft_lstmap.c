/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 13:22:46 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/14 15:12:37 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*cur;
	t_list	*out;
	t_list	*first;
	t_list	*res;

	if (!lst)
		return (NULL);
	cur = lst;
	res = f(cur);
	if ((first = ft_lstnew(res->content, res->content_size)) == NULL)
		return (NULL);
	out = first;
	while (cur->next)
	{
		cur = cur->next;
		res = f(cur);
		if ((out->next = ft_lstnew(res->content, res->content_size)) == NULL)
			return (NULL);
		out = out->next;
	}
	free(out);
	out = NULL;
	return (first);
}
