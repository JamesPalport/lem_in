/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:27:10 by amerrouc          #+#    #+#             */
/*   Updated: 2019/03/01 09:54:47 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H
# include "Libft/includes/libft.h"

typedef struct	s_room
{
	char			*name;
	int				x;
	int				y;
	struct s_room	*next;
}				t_room;

typedef struct	s_routes
{
	char			*path;
	struct s_routes	*next;
}				t_routes;

typedef struct	s_all
{
	int			nb_ants;
	t_room		*rooms;
	int			nb_rooms;
	int			**connec;
	t_room		*start;
	t_room		*end;
	t_routes	*routes;
}				t_all;

int				count_expr(char *line);
char			*read_map(t_all *all, int fd);
int				read_connec(t_all *all, char *line, int fd);
int				reader(t_all *all, int fd);
int				get_routes(t_all *all);

#endif
