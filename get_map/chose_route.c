/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chose_route.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:14:27 by amerrouc          #+#    #+#             */
/*   Updated: 2019/04/12 15:03:56 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static t_routes	**ft_new_selec(t_routes *cursor)
{
	int			len;
	t_routes	**select;

	len = 1;
	if (!cursor)
		return (NULL);
	while ((cursor = cursor->next))
		len++;
	if (!(select = (t_routes **)malloc(sizeof(t_routes *) * (len + 1))))
		return (NULL);
	while (len >= 0)
		select[len--] = NULL;
	return (select);
}

static int	ft_comp_routes(t_routes *route1, t_routes *route2)
{
	int	i;
	int	j;

	i = 1;
	while (i < route1->len)
	{
		j = 1;
		while (j < route2->len)
		{
			if (route1->path[i] == route2->path[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	ft_is_comp(t_routes **select, t_routes *route, int except)
{
	int			n;
	t_routes	*cursor;

	n = 0;
	if (select[0] == NULL)
		return (1);
	while ((cursor = select[n]))
	{
		if (n != except && !ft_comp_routes(cursor, route))
			return (-n);
		n++;
	}
	return (1);
}

static t_routes	*search(t_routes *routes, t_routes *base, int m)
{
	int			i;

	while (routes)
	{
		i = 1;
		while (i < routes->len && i < base->len
				&& routes->path[i] == base->path[i])
			i++;
		if (i == m)
			return (routes);
		routes = routes->next;
	}
	return (NULL);
}

static void	sim_part(t_routes *route1, t_routes route2, int *start, int *end)
{
	int	m;
	int	i;

	m = 1;
	while (m < route1->len && route1->path[m] != route2->path[i])
	{
		i = 1;
		while (i < route2->len && route1->path[m] != route2->path[i])
			i++;
		if (i == route->len)
			m++;
	}
	*start = m;
	while (m < route1->len && i < route2->len
			&& route1->path[m] == route2->path[i])
	{
		m++;
		i++;
	}
	*end = m;
}

static t_routes	*from_to(t_all *all, t_routes *base, int *extr, t_routes *no)
{
	int			i;
	int			*path;
	t_routes	*new;

	i = -1;
	if (!(path = (int)malloc(sizeof(int) * all->nb_rooms)))
		return (NULL);
	while (++i < extr[0])
		path[i] = base->path[i];
}

static void	search_replace(t_all *all, t_routes *route, int conflict, int n)
{
	t_routes	*similar;
	int			m;
	int			i;

	m = 1;
	while (m < all->select[conflict]->len
			&& all->select[conflict]->path[m] != route->path[i])
	{
		i = 1;
		while (i < route->len
				&& all->select[conflict]->path[m] != route->path[i])
			i++;
		if (i == route->len)
			m++;
	}
	similar = search(route->next, all->select[conflict], m);
/*	if (!similar)
	{
		alter_route(all, all->select[conflict], m);
		similar = search(route->next, all->select[conflict], m);
	}*/
	if (similar && ((similar->len + (all->nb_ants / 2))
			< (all->select[conflict]->len + all->nb_ants))
			&& ft_comp_routes(route, similar))
	{
		all->select[conflict] = route;
		all->select[n] = similar;
	}
}

void		chose_route(t_all *all)
{
	t_routes	*cursor;
	int			n;
	int			conflict;

	if (!(all->select = ft_new_selec(all->routes)))
		return ;
	n = 0;
	cursor = all->routes;
	while (cursor)
	{
		if ((conflict = ft_is_comp(all->select, cursor, -1)) == 1)
			all->select[n] = cursor;
		else if (ft_is_comp(all->select, cursor, -conflict) == 1)
			search_replace(all, cursor, -conflict, n);
		if (all->select[n])
			n++;
		cursor = cursor->next;
	}
}
