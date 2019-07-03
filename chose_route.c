/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chose_route.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:14:27 by amerrouc          #+#    #+#             */
/*   Updated: 2019/07/03 15:07:32 by amerrouc         ###   ########.fr       */
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
	int	*yes;

	if (!(yes = ft_newtab(all->nb_rooms)))
		return (NULL);
	j = 0;
	while (all->select[j])
	{
		i = 1;
		if (j != except)
			while (i < all->select[j]->len)
				yes[all->select[j]->path[i++]] = 0;
		j++;
	}
	return (yes);
}

static int		is_ok(t_all *all, int curr, int j, int *yes)
{
	if (curr != j && yes[j] && all->connec[curr][j])
	{
		if (all->score[curr] <= all->score[j])
			return (2);
		else if (all->score[curr] > all->score[j])
			return (1);
	}
	return (0);
}

static t_routes	*reach_begin(t_all *all, int *patch, t_branch *br, int *yes)
{
	t_routes	*new;
	int			curr;
	int			i;
	int			abs;

	abs = 0;
	while (abs < all->nb_rooms && patch[abs] != -1)
		abs++;
	if (abs == all->nb_rooms)
		return (NULL);
	curr = patch[abs - 1];
	i = 1;
	while (i < all->nb_rooms - 1)
	{


	}

	return (new);
}

static t_routes	*from_to(t_all *all, t_routes *base, t_branch *br, int *yes)
{
	int			i;
	int			j;
	int			*patch;
	t_routes	*new;

	i = 0;
	new = NULL;
	if (!(patch = ft_newtab(all->nb_rooms)))
		return (NULL);
	while (!new && i < br->len_finish)
	{
		patch[0] = br->finish[i++];
		j = 1;
		while (!new && j < all->nb_rooms - 1)
		{
			if (is_ok(all, patch[0], j, yes) != 0)
			{
				patch[1] = j;
				new = reach_begin(all, patch, br, yes);
			}
			j++;
		}
	}
	return (new);
}

t_branch		*set_branches(t_all *all, t_routes *route, int c)
{
	t_branch	*br;
	int			extr[2];
	int			i;

	if (!(br = (t_branch *)malloc(sizeof(t_branch))))
		return (NULL);
	sim_part(all->select[c], route, extr);
	br->len_begin = extr[0];
	br->len_finish = all->select[c]->len - extr[1];
	if (!(br->begin = ft_newtab(br->len_begin))
			|| !(br->finish = ft_newtab(br->len_finish)))
		return (0);
	i = -1;
	while (++i < extr[0])
		br->begin[i] = all->select[c]->path[i];
	i = -1;
	while (++i + extr[1] < all->select[c]->len)
		br->begin[i + extr[1]] = all->select[c]->path[i + extr[1]];
	return (br);
}

static t_routes	*search_new(t_all *all, t_routes *route, int c)
{
	t_branch	*br;
	int			*yes;

	if (!(yes = set_forb(all, c)))
		return (NULL);
	br = set_branches(all, route, c);
	from_to(all, all->select[c], br, yes);
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
