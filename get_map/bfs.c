/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 10:49:28 by amerrouc          #+#    #+#             */
/*   Updated: 2019/03/14 11:04:21 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static int		keep_vis(int *to_vis, int size)
{
	int	i;

	i = 0;
	while (i < size)
		if (to_vis[i++])
			return (1);
	return (0);
}

static void		transf_vis(int *to_vis, int *new_vis, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (new_vis[i])
		{
			to_vis[i] = 1;
			new_vis[i] = 0;
		}
		else
			to_vis[i] = 0;
		i++;
	}
}

static void		assign_score(t_all *all, int *to_vis, int *new_vis)
{
	int			i;
	int			j;
	static int	scr;

	i = 0;
	while (i < all->nb_rooms)
	{
		if (to_vis[i])
		{
			to_vis[i] = 0;
			if (!all->score[i])
				all->score[i] = scr;
			j = 1;
			while (j < all->nb_rooms)
			{
				if (i != j && all->connec[i][j] && !all->score[j])
					new_vis[j] = 1;
				j++;
			}
		}
		i++;
	}
	scr++;
	transf_vis(to_vis, new_vis, all->nb_rooms);
}

static void		init_vect(t_all *all, int *to_vis, int *new_vis)
{
	int	i;

	i = 0;
	while (i < all->nb_rooms)
	{
		to_vis[i] = 0;
		new_vis[i] = 0;
		all->score[i++] = 0;
	}
	to_vis[0] = 1;
	all->score[0] = -1;
	all->score[all->nb_rooms - 1] = -1;
}

void			bfs(t_all *all)
{
	int	*to_vis;
	int	*new_vis;

	if (!(all->score = (int *)malloc(sizeof(int) * all->nb_rooms)))
		return ;
	if (!(new_vis = (int *)malloc(sizeof(int) * all->nb_rooms)))
		return ;
	if (!(to_vis = (int *)malloc(sizeof(int) * all->nb_rooms)))
	{
		free(new_vis);
		return ;
	}
	init_vect(all, to_vis, new_vis);
	while (keep_vis(to_vis, all->nb_rooms))
		assign_score(all, to_vis, new_vis);
	free(new_vis);
	free(to_vis);
}
