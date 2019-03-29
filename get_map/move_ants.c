/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 10:38:24 by amerrouc          #+#    #+#             */
/*   Updated: 2019/03/29 14:14:17 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static void	init_ants(int ***paths, int **pos, int nb_ants)
{
	int	i;

	if (!(*paths = (int **)malloc(sizeof(int *) * nb_ants)))
		return ;
	if (!(*pos = (int *)malloc(sizeof(int ) * nb_ants)))
	{
		free(paths);
		*paths = NULL;
		return ;
	}
	i = 0;
	while (i < nb_ants)
	{
		(*pos)[i] = 0;
		(*paths)[i] = NULL;
		i++;
	}
}

static int	*avail_route(t_all *all, int **paths, int *pos)
{
	int			i;
	int			j;
	t_routes	*sel;

	i = 0;
	while (all->select[i])
	{
		j = 0;
		sel = all->select[i];
		while (sel && j < all->nb_ants && paths[j])
		{
			if (paths[j] == sel->path && pos[j] == 1)
				sel = NULL;
			j++;
		}
		if (sel)
			return (sel->path);
		i++;
	}
	return (NULL);
}

static char	*get_name(t_all *all, int num)
{
	int		i;
	t_room	*cursor;

	i = 1;
	if (num == 0)
		return (all->start->name);
	if (num == all->nb_rooms - 1)
		return (all->end->name);
	cursor = all->rooms;
	while (i++ != num)
		cursor = cursor->next;
	return (cursor->name);
}

static int	display_mov(t_all *all, int **paths, int *pos)
{
	int		end;
	int		i;
	char	*name;

	end = 1;
	i = 0;
	while (i < all->nb_ants && paths[i])
	{
		if (pos[i] != -1)
		{
			name = get_name(all, paths[i][pos[i]]);
			ft_printf("L%d-%s ", i, name);
		}
		if (paths[i][pos[i]] == all->nb_rooms - 1)
			pos[i] = -1;
		else if (end && pos[i] != -1)
			end = 0;
		i++;
	}
	write(1, "\n", 1);
	return (end);
}

void	move_ants(t_all *all)
{
	int	**paths;
	int	*pos;
	int	i;
	int	end;

	end = 0;
	init_ants(&paths, &pos, all->nb_ants);
	if (!paths || !pos)
		return ;
	while (!end)
	{
		i = 0;
		while (i < all->nb_ants && paths[i])
			if (pos[i++] != -1)
				pos[i - 1]++;
		while (i < all->nb_ants && (paths[i] = avail_route(all, paths, pos)))
			pos[i++] = 1;
		end = display_mov(all, paths, pos);
	}
}
