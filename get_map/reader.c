/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:15:06 by amerrouc          #+#    #+#             */
/*   Updated: 2019/02/21 12:35:57 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

int			count_expr(char *line)
{
	int	i;
	int	nb_expr;

	i = ft_strlen(line) - 1;
	nb_expr = 0;
	if (line[0] == '#')
	{
		if (i > 1 && line[1] == '#')
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

int			reader(t_rd *rd, int fd)
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
	if (rd->nb_ants <= 0 || rd->nb_rooms <= 1 || !line)
		return (0);
	return (read_connec(rd, line, fd));
}
