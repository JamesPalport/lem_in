/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:25:39 by amerrouc          #+#    #+#             */
/*   Updated: 2019/03/19 16:09:04 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static void	append_route(t_all *all, t_routes *new)
{
	t_routes	*cursor;

	new->next = NULL;
	if (all->routes)
	{
		cursor = all->routes;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = new;
	}
	else
		all->routes = new;
}

static int	save_route(t_all *all, int *route)
{
	int			i;
	int			j;
	t_routes	*new;

	i = 0;
	while (route[i] != -1 && i < all->nb_rooms)
		i++;
	if (!(new = (t_routes *)malloc(sizeof(t_routes))))
		return (0);
	if (!(new->path = (int *)malloc(sizeof(int) * i)))
	{
		free(new);
		return (0);
	}
	new->len = --i;
	j = 0;
	while (i >= 0)
	{
		new->path[j] = route[i];
		i--;
		j++;
	}
	append_route(all, new);
	return (1);
}

static int	is_auth(t_all *all, int curr, int i, int *route)
{
	int	j;

	j = 0;
	while (j < all->nb_rooms && route[j] != -1)
		if (route[j++] == i)
			return (0);
	if (i != curr && all->connec[curr][i]
			&& ((all->score[curr] == -1)
				|| all->score[curr] >= all->score[i]))
		return (1);
	return (0);
}

int			check_new_route(t_all *all, int *route)
{
	int			j;
	int			i;
	int			same;
	int			route_len;
	t_routes	*cursor;

	route_len = 0;
	while (route_len < all->nb_rooms && route[route_len] != -1)
		route_len++;
	cursor = all->routes;
	while (cursor)
	{
		j = route_len - 1;
		i = 0;
		while (i < cursor->len && j >= 0 && cursor->path[i] == route[j])
		{
			i++;
			j--;
		}
		if (i == cursor->len)
			return (0);
		cursor = cursor->next;
	}
	return (1);
}

static void	go_next(t_all *all, int *route)
{
	int	i;
	int	abs;
	int	curr;

	abs = 0;
	while (abs < all->nb_rooms && route[abs] != -1)
		abs++;
	if (abs == all->nb_rooms)
		return ;
	curr = route[abs - 1];
	i = 0;
	while (i < all->nb_rooms - 1)
	{
		if (is_auth(all, curr, i, route))
		{
			route[abs] = i;
			if (!route[abs])
				save_route(all, route);
			else
				go_next(all, route);
			route[abs] = -1;
		}
		i++;
	}
}

int			get_routes(t_all *all)
{
	int	*route;
	int	i;

	if (!(route = (int *)malloc(sizeof(int) * all->nb_rooms)))
		return (0);
	i = 0;
	while (i < all->nb_rooms)
		route[i++] = -1;
	route[0] = all->nb_rooms - 1;
	i = 0;
	while (i < all->nb_rooms - 1)
	{
		if (all->connec[all->nb_rooms - 1][i] && all->score[i])
		{
			route[1] = i;
			go_next(all, route);
			route[1] = -1;
		}
		i++;
	}
	free(route);
	return (1);
}
