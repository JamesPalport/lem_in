/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:15:06 by amerrouc          #+#    #+#             */
/*   Updated: 2019/02/18 16:13:34 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static char	*get_rooms(t_rd *rd)
{
	t_room	*cursor;
	char	*line;
	int		ok;
	int		i;

	rd->nb_rooms = 0;
	cursor = rd->rooms;
	ok = 1;
	while (ok && get_next_line(0, &line) > 0)
	{
		if (!(cursor = (t_room *)malloc(sizeof(t_room))))
			return (NULL);
		i = 0;
		while (line[i])
			if (line[i] ==  
		if (line[0] != '#')
		{
			while (ft_isdigit(line[i]))
				i--;
			cursor->y = ft_atoi(line + --i + 2);
			while (ft_isdigit(line[i]))
				i--;
			cursor->x = ft_atoi(line + --i + 2);
			cursor->name = ft_strsub(line, 0, i);
		}

	}
}

int			reader(t_rd *rd)
{
	char	*line;

	if (get_next_line(0, &line) <= 0)
		return (0);
	rd->nb_ants = ft_atoi(line);
	free(line);
	if (rd->nb_ants <= 0)
		return (0);
	line = get_rooms(rd);
	if (!line)
		return (0);
	return (get_connec(rd, line));
}
