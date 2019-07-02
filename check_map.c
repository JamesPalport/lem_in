/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 20:03:23 by amerrouc          #+#    #+#             */
/*   Updated: 2019/03/10 22:25:56 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static int	check_room(t_all *all, t_room *current, int i)
{
	t_room	*cursor;
	int		j;

	j = 0;
	cursor = all->rooms;
	while (cursor)
	{
		if (i == j)
		{
			j++;
			cursor = cursor->next;
		}
		if (cursor && (!ft_strcmp(current->name, cursor->name)
					|| (current->x == cursor->x && current->y == cursor->y)))
			return (0);
		else if (cursor)
			cursor = cursor->next;
		j++;
	}
	return (1);
}

int			check_map(t_all *all)
{
	t_room	*current;
	int		i;

	current = all->rooms;
	i = 0;
	while (current)
	{
		if (!ft_strcmp(current->name, all->start->name)
				|| (current->x == all->start->x
					&& current->y == all->start->y)
				|| !ft_strcmp(current->name, all->end->name)
				|| (current->x == all->end->x
					&& current->y == all->end->y))
			return (0);
		check_room(all, current, i);
		current = current->next;
		i++;
	}
	return (1);
}
