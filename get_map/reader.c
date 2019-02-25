/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:15:06 by amerrouc          #+#    #+#             */
/*   Updated: 2019/02/25 10:40:01 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

int			count_expr(char *line)
{
	int	i;
	int	count_sp;
	int	count_tr;

	i = ft_strlen(line) - 1;
	count_sp = 0;
	count_tr = 0;
	if (i > 1 && line[0] == '#' && line[1] == '#')
		return (-1);
	else if (line[0] == '#')
		return (-2);
	while (i > 0)
	{
		if (line[i] == ' ')
			count_sp++;
		else if (line[i] == '-')
			count_tr++;
		while (i && (line[i] == ' ' || line[i] == '-'))
			i--;
		while (i && ft_isalnum(line[i]))
			i--;
	}
	return (count_tr ? count_tr + 1 : count_sp + 1);
}

int			reader(t_all *all, int fd)
{
	char	*line;
	int		c;
	int		dst;

	line = NULL;
	if (get_next_line(fd, &line) < 0)
		return (0);
	all->nb_ants = ft_atoi(line);
	free(line);
	line = read_map(all, fd);
	if (all->nb_ants <= 0 || all->nb_rooms <= 1 || !line)
		return (0);
	return (read_connec(all, line, fd));
}
