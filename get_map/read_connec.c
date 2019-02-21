/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_connec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:35:10 by amerrouc          #+#    #+#             */
/*   Updated: 2019/02/21 12:47:57 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static int	get_num(t_rd *rd, char *line)
{
	int		i;
	int		len1;
	t_room	*cursor;

	len1 = 0;
	while (line[len1] && line[len1] != '-')
		len1++;
	i = 1;
	if (!ft_strncmp(line, rd->start->name, len1))
		i = 0;
	else if (!ft_strncmp(line, rd->end->name, len1))
		i = rd->nb_rooms - 1;
	else
	{
		cursor = rd->rooms;
		while (cursor && (ft_strncmp(line, cursor->name, len1)))
		{
			i++;
			cursor = cursor->next;
		}
	}
	return (i);
}

static int	init_connec(t_rd *rd)
{
	int	i;
	int	j;

	j = 0;
	if (!(rd->connec = (int **)malloc(sizeof(int *) * rd->nb_rooms)))
		return (0);
	while (j < rd->nb_rooms)
	{
		if (!(rd->connec[j] = (int *)malloc(sizeof(int) * rd->nb_rooms)))
			return (0);
		i = 0;
		while (i < rd->nb_rooms)
			rd->connec[j][i++] = 0;
		j++;
	}
	return (1);
}

static void	get_connec(t_rd *rd, char *line)
{
	int	i;
	int	j;

	i = get_num(rd, line);
	j = 0;
	while (line[j] && line[j] != '-')
		j++;
	j = get_num(rd, line + j + 1);
	if (!rd->connec[i][j])
	{
		rd->connec[i][j] = 1;
		rd->connec[j][i] = 1;
		rd->connec[j][j]++;
		rd->connec[i][i]++;
	}
}

int			read_connec(t_rd *rd, char *line, int fd)
{
	int	c;

	init_connec(rd);
	if ((c = count_expr(line)) == 2)
	{
		get_connec(rd, line);
	}
	free(line);
	while (get_next_line(fd, &line)
			&& ((c = count_expr(line)) == 2 || line[0] == '#'))
	{
		if (c == 2 && line[0] != '#')
			get_connec(rd, line);
		ft_strdel(&line);
	}
	if (count_expr(line) == 2)
		get_connec(rd, line);
	ft_strdel(&line);
	return (1);
}
