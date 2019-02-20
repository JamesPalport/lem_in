/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:15:06 by amerrouc          #+#    #+#             */
/*   Updated: 2019/02/20 16:54:07 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static int		count_expr(char *line)
{
	int	i;
	int	nb_expr;

	i = ft_strlen(line) - 1;
	nb_expr = 0;
	if (line[0] == '#')
	{
		if (i >1 && line[1] == '#')
			return (-1);
		else
			return (-2);
	}
	while (i > 0)
	{
		nb_expr++;
		while (i && (line[i] == ' ' || line[i] == '-'))
			i--;
		while (i && ft_isalnum(line[i]))
			i--;
		}
	return (nb_expr);
}

static t_room	*new_room(void)
{
	t_room	*new;

	if (!(new = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	new->name = NULL;
	new->x = 0;
	new->y = 0;
	new->next = NULL;
	return (new);
}

static int		get_room(t_rd *rd, char *line, int dst)
{
	t_room	*cursor;
	t_room	*assign;
	int		i;

	if (!(cursor = new_room()))
		return (0);
	i = ft_strlen(line) - 1;
	while (i && ft_isdigit(line[i]))
		i--;
	cursor->y = ft_atoi(line + --i + 2);
	while (i && ft_isdigit(line[i]))
		i--;
	cursor->x = ft_atoi(line + --i + 2);
	cursor->name = ft_strsub(line, 0, i + 1);
	assign = rd->rooms;
	if (dst == 0)
	{
		while (assign && assign->next)
			assign = assign->next;
		if (assign)
			assign->next = cursor;
		else
			rd->rooms = cursor;
	}
	else if (dst == 1)
		rd->start = cursor;
	else if (dst == 2)
		rd->end = cursor;
	rd->nb_rooms += 1;
	return (1);
}

static char		*read_map(t_rd *rd, int fd)
{
	int		dst;
	int		c;
	char	*line;

	while (get_next_line(fd, &line) > 0
			&& ((c = count_expr(line)) == 3 || c < 0 || line[0] == '#'))
	{
		if (c == 3)
			dst = 0;
		else if (c == -1)
		{
			if (!ft_strcmp("start", line + 2))
				dst = 1;
			else if (!ft_strcmp("end", line + 2))
				dst = 2;
			else
			{
				free(line);
				return (NULL);
			}
		}
		if (dst != 0)
		{
			free(line);
			if (get_next_line(fd, &line) < 0 || count_expr(line) != 3)
			{
				free(line);
				return (NULL);
			}
		}
		get_room(rd, line, dst);
		free(line);
	}
	if (c != 2)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static int		get_num(t_rd *rd, char *line)
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
	rd->connec[i][j]++;
	rd->connec[j][i]++;
	rd->connec[j][j]++;
	rd->connec[i][i]++;
	free(line);
}

int				reader(t_rd *rd, int fd)
{
	char	*line;
	int		c;
	int		dst;

	line = NULL;
	 if (get_next_line(fd, &line) < 0)
		 return (0);
	rd->nb_ants = ft_atoi(line);
	free(line);
	line = read_map(rd, fd);
	if (rd->nb_ants <= 0 || rd->nb_rooms <= 1)
		return (0);
	init_connec(rd);
	if (count_expr(line) == 2)
		get_connec(rd, line);
	while (get_next_line(fd, &line) && count_expr(line) == 2)
		get_connec(rd, line);
	if (count_expr(line) == 2)
			get_connec(rd, line);
	return (1);
}
