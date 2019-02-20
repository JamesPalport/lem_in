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
	while (rd->connec && rd->connec[i] && i < rd->nb_rooms)
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
	free_all(&rd);
	return (1);
}
