/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chose_route.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:14:27 by amerrouc          #+#    #+#             */
/*   Updated: 2019/07/02 15:26:21 by amerrouc         ###   ########.fr       */
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
	int	k;

	i = 1;
	k = 0;
	extr[0] = 0;
	extr[1] = 0;
	while (i < route1->len && i + k < route2->len
			&& route1->path[i] != route2->path[i + k])
	{
		k = 0;
		while (i + k < route2->len && route1->path[i] != route2->path[i + k])
			k++;
		if (route1->path[i] != route2->path[i + k])
			i++;
	}
	extr[0] = i;
	while (i < route1->len && i + k < route2->len
			&& route1->path[i] != route2->path[i + k])
		i++;
	extr[1] = i;
}


static int		*set_forb(t_all *all, int except)
{
	int	i;
	int	j;
	int	*no;

	if (!(no = ft_newtab(all->nb_rooms)))
		return (NULL);
	j = 0;
	while (all->select[j])
	{
		i = 1;
		if (j != except)
			while (i < all->select[j]->len)
				no[all->select[j]->path[i++]] = 0;
		j++;
	}
	return (no);
}

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
	(void)no;
	//reach_extr(all, no, path);
	i = extr[0];
	while (path[i] != -1)
		i++;
	if (path[i - 1] != base->path[extr[1]])
		return (NULL);
	return (new);
}

static t_routes	*search_new(t_all *all, t_routes *route, int c)
{
	int	extr[2];
	int	*no;

	if (!(no = set_forb(all, c)))
		return (NULL);
	sim_part(all->select[c], route, extr);
	from_to(all, all->select[c], extr, no);
	return (NULL);
}


static t_routes	*search_registered(t_all *all, t_routes *route, int c)
{
	t_routes	*cursor;

	cursor = route->next;
	while (cursor)
	{
		if (c == ft_is_comp(all->select, cursor, -1)
				&& ft_is_comp(all->select, cursor, c) == 1
				&& ft_comp_routes(cursor, route))
			return (cursor);
		cursor = cursor->next;
	}
	return (NULL);
}

static t_routes	*search_replace(t_all *all, t_routes *route, int c)
{
	t_routes	*similar;

	similar = search_registered(all, route, c);
	if (!similar)
		similar = search_new(all, route, c);
	if (similar && ((similar->len + (all->nb_ants / 2))
			< (all->select[c]->len + all->nb_ants))
			&& ft_comp_routes(route, similar))
		all->select[c] = route;
	return (similar);
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
			search_replace(all, cursor, -conflict);
		if (all->select[n])
			n++;
		cursor = cursor->next;
	}
}
