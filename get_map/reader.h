#ifndef READER_H
# define READER_H
# include "Libft/includes/libft.h"

typedef struct	s_room
{
	char	*name;
	int		x;
	int		y;
	s_room	*next;
}				t_room;

typedef struct	s_rd
{
	int		nb_ants;
	t_room	*rooms;
	int		nb_rooms;
	int		**coonec;
	t_room	*start;
	t_room	*end;
}				t_rd;

int				reader(t_rd *rd);

#endif
