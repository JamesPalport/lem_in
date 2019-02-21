/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:15:32 by amerrouc          #+#    #+#             */
/*   Updated: 2019/02/21 12:53:29 by amerrouc         ###   ########.fr       */
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
	new->next = NULL;
	return (new);
}

static void		assign_room(t_rd *rd, t_room *cursor, int dst)
{
	t_room	*assign;

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
}

static int		get_room(t_rd *rd, char *line, int dst)
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
	assign_room(rd, cursor, dst);
	return (1);
}

static int		handle_dst(int c, char *line)
{
	int	dst;

	if (c >= 3)
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
			dst = -1;
		}
	}
	return (dst);
}

char			*read_map(t_rd *rd, int fd)
{
	int		dst;
	int		c;
	char	*line;

	while (get_next_line(fd, &line) > 0
			&& ((c = count_expr(line)) == 3 || c < 0 || line[0] == '#'))
	{
		if ((dst = handle_dst(c, line)) < 0)
			return (NULL);
		if (dst != 0)
		{
			free(line);
			if (get_next_line(fd, &line) < 0 || count_expr(line) < 3)
				ft_strdel(&line);
		}
		get_room(rd, line, dst);
		ft_strdel(&line);
	}
	if (c != 2)
		ft_strdel(&line);
	return (line);
}
