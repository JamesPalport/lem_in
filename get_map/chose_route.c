/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chose_route.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:14:27 by amerrouc          #+#    #+#             */
/*   Updated: 2019/05/28 14:53:14 by amerrouc         ###   ########.fr       */
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

static void	sim_part(t_routes *route1, t_routes *route2, int *extr)
{
	int	i;

	i = 1;
	if (route1->path[1] == route2->path[1])
	{
		*(extr++) = 0;
		while (i < route1->len && i < route2->len
				&& route1->path[i] == route2->path[i])
			i++;
	}
	else
	{
		extr[1] = route1->len;
		while (i < route1->len && i < route2->len
				&& route1->path[i] != route2->path[i])
			i++;
	}
	*extr = i - 1;
}
/*
	int	m;
	int	i;

	m = 1;
	while (m < route1->len && route1->path[m] != route2->path[i])
	{
		i = 1;
		while (i < route2->len && route1->path[m] != route2->path[i])
			i++;
		if (i == route2->len)
			m++;
	}
	extr[0] = m;
	while (m < route1->len && i < route2->len
			&& route1->path[m] == route2->path[i])
	{
		no[route1->path[m]] = 0;
		m++;
		i++;
	}
	no[route1->path[extr[0]]] = 1;
	no[route1->path[extr[1]]] = 1;
	extr[1] = m;
}*/
/*
static void		set_forb(t_all *all, int *no)
{
	int	i;
	int	j;

	j = 0;
	while (all->select[j])
	{
		i = 1;
		while (i < all->select[j]->len)
			no[all->select[j]->path[i++]] = 0;
		j++;
	}
}
*/
static t_routes	*search(t_all *all, t_routes *routes, int c)
{
	int	extr[2];
	int	i;

	sim_part(routes, all->select[c], extr);
	ft_printf("extr :%d %d\n", extr[0], extr[1]);
	while (routes->next)
	{
		routes = routes->next;
		i = 1;
		while (i < all->select[c]->len && i < routes->len
				&& routes->path[i] == all->select[c]->path[extr[0]]
				&& routes->path[i] != all->select[c]->path[extr[0]])
			i++;
		if (i != all->select[c]->len)
		{
			while (i < all->select[c]->len
					&& routes->path[i] != all->select[c]->path[extr[1]])
				i++;
		}
	}
	return (NULL);
}
/*
static t_routes	*from_to(t_all *all, t_routes *base, int *extr, int *no)
{
	int			i;
	int			*path;
	t_routes	*new;

	i = -1;
	new = NULL;
	if (!(path = (int *)malloc(sizeof(int) * all->nb_rooms)))
		return (NULL);
	while (++i < extr[0])
		path[i] = base->path[i];
	while (i < all->nb_rooms)
		path[i++] = -1;
	set_forb(all, no);
	//reach_extr(all, no, path);
	i = extr[0];
	while (path[i] != -1)
		i++;
	if (path[i - 1] != base->path[extr[1]])
		return (NULL);
	return (new);
}
*/
static void	search_replace(t_all *all, t_routes *route, int c, int n)
{
	t_routes	*similar;

	similar = search(all, route, c);
/*	if (!similar)
	{
		alter_route(all, all->select[c], m);
		similar = search(route->next, all->select[c], m);
	}*/
	if (similar && ((similar->len + (all->nb_ants / 2))
			< (all->select[c]->len + all->nb_ants))
			&& ft_comp_routes(route, similar))
	{
		all->select[c] = route;
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
