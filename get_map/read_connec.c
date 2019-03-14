/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_connec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:35:10 by amerrouc          #+#    #+#             */
/*   Updated: 2019/03/05 12:51:26 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static int	get_num(t_all *all, char *line)
{
	int		i;
	int		len1;
	t_room	*cursor;

	len1 = 0;
	while (line[len1] && line[len1] != '-')
		len1++;
	cursor = all->rooms;
	i = 1;
	if (!ft_strncmp(line, all->start->name, len1))
		return (0);
	else if (!ft_strncmp(line, all->end->name, len1))
		return (all->nb_rooms - 1);
	else
	{
		while (cursor && (ft_strncmp(line, cursor->name, len1)))
		{
			i++;
			cursor = cursor->next;
		}
	}
	if (!cursor)
		return (-1);
	return (i);
}

static int	init_connec(t_all *all)
{
	int	i;
	int	j;

	j = 0;
	if (!(all->connec = (int **)malloc(sizeof(int *) * all->nb_rooms)))
		return (0);
	while (j < all->nb_rooms)
	{
		if (!(all->connec[j] = (int *)malloc(sizeof(int) * all->nb_rooms)))
			return (0);
		i = 0;
		while (i < all->nb_rooms)
			all->connec[j][i++] = 0;
		j++;
	}
	return (1);
}

static int	get_connec(t_all *all, char *line)
{
	int	i;
	int	j;

	i = get_num(all, line);
	j = 0;
	while (line[j] && line[j] != '-')
		j++;
	j = get_num(all, line + j + 1);
	if (i < 0 || j < 0)
		return (0);
	if (!all->connec[i][j])
	{
		all->connec[i][j] = 1;
		all->connec[j][i] = 1;
		all->connec[j][j]++;
		all->connec[i][i]++;
	}
	return (1);
}

int			read_connec(t_all *all, char *line, int fd)
{
	int	c;
	int	d;

	init_connec(all);
	d = 0;
	if ((c = count_expr(line)) == 2)
	{
		d = get_connec(all, line);
	}
	free(line);
	if (!d)
		return (0);
	while (get_next_line(fd, &line)
			&& ((c = count_expr(line)) == 2 || line[0] == '#'))
	{
		if (c == 2 && line[0] != '#')
			d = get_connec(all, line);
		ft_strdel(&line);
	}
	if (count_expr(line) == 2)
		d = get_connec(all, line);
	ft_strdel(&line);
	return (d);
}
