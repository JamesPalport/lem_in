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

typedef struct	s_rd
{
	int		nb_ants;
	t_room	*rooms;
	int		nb_rooms;
	int		**connec;
	t_room	*start;
	t_room	*end;
}				t_rd;

int				count_expr(char *line);
char			*read_map(t_rd *rd, int fd);
int				read_connec(t_rd *rd, char *line, int fd);
int				reader(t_rd *rd, int fd);

#endif
