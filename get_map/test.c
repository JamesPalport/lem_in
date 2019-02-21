#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "reader.h"

void	free_all(t_rd *rd)
{
	t_room	*cursor;
	t_room	*del;
	int		i;

	cursor = rd->rooms;
	while (cursor)
	{
		del = cursor;
		cursor = cursor->next;
		free(del->name);
		free(del);
	}
	i = 0;
	while (rd->connec && i < rd->nb_rooms && rd->connec[i])
		free(rd->connec[i++]);
	if (rd->connec)
		free(rd->connec);
	if (rd->start)
		free(rd->start->name);
	free(rd->start);
	if (rd->end)
		free(rd->end->name);
	free(rd->end);
}

void	display_read(t_rd *rd)
{
	int		i;
	int		j;
	t_room	*cursor;

	ft_printf("nombre de fourmis\t:%d\n", rd->nb_ants);
	ft_printf("nombre de salles\t:%d\n", rd->nb_rooms);
	cursor = rd->start;
	ft_printf("debut\t:%s\tx = %d\ty = %d\n", cursor->name, cursor->x, cursor->y);
	cursor = rd->end;
	ft_printf("fin\t:%s\tx = %d\ty = %d\n", cursor->name, cursor->x, cursor->y);
	cursor = rd->rooms;
	while (cursor)
	{
		ft_printf("name =%s\tx = %d\ty = %d\n", cursor->name, cursor->x, cursor->y);
		cursor = cursor->next;
	}
	ft_printf("connexions\n");
	j = 0;
	while (j < rd->nb_rooms)
	{
		i = 0;
		while (i < rd->nb_rooms)
			ft_printf("%4d", rd->connec[j][i++]);
		ft_printf("\n");
		j++;
	}
}

int	main(void)
{
	int		fd;
	t_rd	rd;

	rd.nb_ants = 0;
	rd.rooms = NULL;
	rd.nb_rooms = 0;
	rd.connec = NULL;
	rd.start = NULL;
	rd.end = NULL;
	fd = open("map", O_RDONLY);
	reader(&rd, fd);
	close(fd);
	display_read(&rd);
	free_all(&rd);
	return (1);
}
