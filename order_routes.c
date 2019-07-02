/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chose_routes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:34:14 by amerrouc          #+#    #+#             */
/*   Updated: 2019/03/21 15:52:15 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static t_routes	*get_first(t_routes *routes)
{
	t_routes	*cursor1;
	t_routes	*cursor2;
	t_routes	*prev1;

	cursor1 = routes;
	prev1 = NULL;
	cursor2 = routes;
	while (cursor2->next)
	{
		if (cursor1->len > cursor2->next->len)
		{
			prev1 = cursor2;
			cursor1 = cursor2->next;
		}
		cursor2 = cursor2->next;
	}
	if (prev1)
	{
		prev1->next = cursor1->next;
		cursor1->next = routes;
	}
	return (cursor1);
}

static void		move_route(t_routes *mv, t_routes *prev, t_routes *first)
{
	prev->next = mv->next;
	mv->next = first->next;
	first->next = mv;
}

static void		swap_routes(t_routes *routes)
{
	t_routes	*cursor1;
	t_routes	*prev1;
	t_routes	*cursor2;
	t_routes	*min;

	prev1 = routes;
	cursor1 = routes;
	while (cursor1->next)
	{
		min = cursor1->next;
		cursor2 = min;
		while (cursor2->next)
		{
			if (min->len > cursor2->next->len)
			{
				min = cursor2->next;
				prev1 = cursor2;
			}
			cursor2 = cursor2->next;
		}
		if (min != cursor1->next)
			move_route(min, prev1, cursor1);
		cursor1 = cursor1->next;
	}
}

t_routes		*order_routes(t_routes *routes)
{
	if (!routes)
		return (NULL);
	routes = get_first(routes);
	if (routes->next)
		swap_routes(routes);
	return (routes);
}
