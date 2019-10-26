/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:27:10 by amerrouc          #+#    #+#             */
/*   Updated: 2019/07/03 15:07:35 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H
# include "libft.h"

typedef struct	s_branch
{
	int	len_begin;
	int	len_finish;
	int	*begin;
	int	*finish;
}				t_branch;

typedef struct	s_tmpr
{
	int	*to_vis;
	int	*new_vis;
}				t_tmpr;

typedef struct	s_room
{
	char			*name;
	int				x;
	int				y;
	int				empty;
	struct s_room	*next;
}				t_room;

typedef struct	s_routes
{
	int				*path;
	int				len;
	struct s_routes	*next;
}				t_routes;

typedef struct	s_all
{
	int			nb_ants;
	t_room		*rooms;
	int			nb_rooms;
	int			**connec;
	int			*score;
	int			max_score;
	t_room		*start;
	t_room		*end;
	t_routes	*routes;
	t_routes	**select;
}				t_all;

int				*ft_newtab(int len);
int				count_expr(char *line);
char			*read_map(t_all *all, int fd);
void			ignore_comments(char **line, int fd);
int				read_connec(t_all *all, char *line, int fd);
int				reader(t_all *all, int fd);
int				get_routes(t_all *all);
void			append_route(t_all *all, t_routes *new);
int				check_map(t_all *all);
void			bfs(t_all *all, t_tmpr *tmp);
t_routes		*order_routes(t_routes *routes);
void			chose_route(t_all *all);
void			move_ants(t_all *all);
void			display_routes(t_all *all);
void			display_select(t_all *all);

#endif
