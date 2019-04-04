/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:15:32 by amerrouc          #+#    #+#             */
/*   Updated: 2019/03/21 11:36:12 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static t_room	*new_room(void)
{
	t_room	*new;

	if (!(new = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	new->name = NULL;
	new->x = 0;
	new->y = 0;
	new->empty = 1;
	new->next = NULL;
	return (new);
}

static void		assign_room(t_all *all, t_room *cursor, int dst)
{
	t_room	*assign;

	assign = all->rooms;
	if (dst == 0)
	{
		while (assign && assign->next)
			assign = assign->next;
		if (assign)
			assign->next = cursor;
		else
			all->rooms = cursor;
	}
	else if (dst == 1)
		all->start = cursor;
	else if (dst == 2)
		all->end = cursor;
	all->nb_rooms += 1;
}

static int		get_room(t_all *all, char *line, int dst)
{
	t_room	*cursor;
	int		i;

	if (!line)
		return (0);
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
	assign_room(all, cursor, dst);
	free(line);
	return (1);
}

static void		ignore_comments(char **line, int fd)
{
	while (((*line)[0] == '#' && (*line)[1] != '#') || (*line)[0] == 0)
	{
		free(*line);
		get_next_line(fd, line);
	}
}

static int		handle_dst(char **line, int fd)
{
	int	i;
	int	dst;

	if (((*line)[0] == '#' && (*line)[1] != '#') || (*line)[0] == 0)
		ignore_comments(line, fd);
	else if ((*line)[0] == '#' && (*line)[1] == '#')
	{
		if (!ft_strcmp("start", *line + 2))
			dst = 1;
		else if (!ft_strcmp("end", *line + 2))
			dst = 2;
		else
			return (-1);
		free(*line);
		get_next_line(fd, line);
		ignore_comments(line, fd);
		return (dst);
	}
	dst = -1;
	i = 0;
	while ((*line)[i])
	{
		if (dst != 0 && (*line)[i] == ' ')
			dst = 0;
		if ((*line)[i] == '-')
			return (-1);
		i++;
	}
	return (dst);
}


char			*read_map(t_all *all, int fd)
{
	int		dst;
	char	*line;

	dst = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '#' && line[1] != '#')
			ignore_comments(&line, fd);
		if ((dst = handle_dst(&line, fd)) < 0)
			return (line);
		get_room(all, line, dst);
	}
	return (line);
}
