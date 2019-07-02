/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 10:49:28 by amerrouc          #+#    #+#             */
/*   Updated: 2019/03/21 12:07:22 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static int		keep_vis(int *to_vis, int size, int exp_score, int max_score)
{
	int	i;

	i = 0;
	if (exp_score > 0 && exp_score <= max_score)
		return (0);
	if (exp_score == -1 && to_vis[size - 1])
		return (0);
	while (i < size)
		if (to_vis[i++])
			return (1);
	return (0);
}

static void		transf_vis(int **to_vis, int **new_vis)
{
	int	*tmp;

	tmp = *to_vis;
	*to_vis = *new_vis;
	*new_vis = tmp;
}

static void		assign_score(t_all *all, int **to_vis, int **new_vis)
{
	int			i;
	int			j;

	i = 0;
	all->max_score++;
	while (i < all->nb_rooms - 1)
	{
		if ((*to_vis)[i])
		{
			(*to_vis)[i] = 0;
			if (!all->score[i])
				all->score[i] = all->max_score;
			j = 1;
			while (j < all->nb_rooms)
			{
				if (i != j && all->connec[i][j] && all->score[j] <= 0)
					(*new_vis)[j] = 1;
				j++;
			}
		}
		i++;
	}
	transf_vis(to_vis, new_vis);
}

static int		init_vect(t_all *all, t_tmpr *tmp)
{
	int	i;

	if (!(tmp->to_vis = (int *)malloc(sizeof(int) * all->nb_rooms)))
		return (0);
	if (!(tmp->new_vis = (int *)malloc(sizeof(int) * all->nb_rooms)))
		return (0);
	i = 0;
	while (i < all->nb_rooms)
	{
		tmp->to_vis[i] = 0;
		tmp->new_vis[i] = 0;
		all->score[i++] = 0;
	}
	tmp->to_vis[0] = 1;
	all->score[0] = -1;
	all->score[all->nb_rooms - 1] = -1;
	return (1);
}

void			bfs(t_all *all, int exp_score, t_tmpr *tmp)
{
	if (!all->score
			&& !(all->score = (int *)malloc(sizeof(int) * all->nb_rooms)))
		return ;
	if (!tmp->new_vis && !tmp->to_vis)
		if (!init_vect(all, tmp))
			return ;
	while (keep_vis(tmp->to_vis, all->nb_rooms, exp_score, all->max_score))
		assign_score(all, &(tmp->to_vis), &(tmp->new_vis));
	tmp->to_vis[all->nb_rooms - 1] = 0;
}
