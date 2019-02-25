/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:25:39 by amerrouc          #+#    #+#             */
/*   Updated: 2019/02/25 16:07:39 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static int		len_str(int nb_rooms)
{
	int			c;
	int			tmp;

	tmp = nb_rooms;
	c = 1;
	while (tmp >= 10)
	{
		tmp /= 10;
		c++;
	}
	return ((c + 1) * nb_rooms + 1);
}

static int		append_route(t_all *all, char	*route)
{
	t_routes	*new;
	t_routes	*cursor;

	if (!(new = (t_routes *)malloc(sizeof(t_routes))))
		return (0);
	if (!(new->path = ft_strdup(route)))
	{
		free(new);
		return (0);
	}
	new->next = NULL;
	if (!all->routes)
		all->routes = new;
	cursor = all->routes;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = new;
	return (1);
}

static void		put_num(char *str, int nb)
{
	int	c;
	int	i;

	c = 1;
	while (nb / c >= 10)
		c *= 10;
	i = 0;
	while (nb && c)
	{
		str[i] = (nb / c) % 10 + '0';
		nb -= (nb / c) * c;
		c /= 10;
		i++;
	}
	str[i] = '.';
}

static int		is_poss(t_all *all, char *route, int j, int i)
{
	int			n;
	char		*verif;
	int			len;
	t_routes	*cursor;

	if (i == j || all->connec[j][i] == 0)
		return (0);
	n = 0;
	verif = ft_itoa(i);
	len = ft_strlen(verif);
	while (route[n] && ft_strncmp(route + n, verif, len))
	{
		while (route[n] && route[n] != '.')
			n++;
		if (route[n])
			n++;
	}
	free(verif);
	if (route[n])
		return (0);
	cursor = all->routes;
	while (cursor)
	{
		if (!ft_strcmp(cursor->path, route))
			return (0);
		cursor = cursor->next;
	}
	return (1);
}

static int		pos_last(char *route)
{
	int	i;

	i = ft_strlen(route);
	i -= 2;
	while (i > 0 && route[i] != '.')
		i--;
	return (i < 0 ? 0 : i);
}

static void		rmv_last(char *route)
{
	int	i;
	int	len;

	len = ft_strlen(route);
	i = pos_last(route);
	while (i < len)
		route[i++] = '\0';
}

static int		go_next(t_all *all, char *route)
{
	int	curr;
	int	i;

	if (!ft_strlen(route))
		return (0);
	curr = ft_atoi(route + pos_last(route));
	i = 1;
	while (i < all->nb_rooms)
	{
		if (is_poss(all, route, curr, i))
		{
			put_num(route, i);
			if (i == all->nb_rooms - 1)
			{
				append_route(all, route);
				rmv_last(route);
				return (1);
			}
			else
				go_next(all, route);
		}
		i++;
	}
	rmv_last(route);
	return (0);
}

int				get_routes(t_all *all)
{
	char	*route;
	int		i;

	route = ft_strnew(len_str(all->nb_rooms));
	put_num(route, 0);
	go_next(all, route);
	return (1);
}
