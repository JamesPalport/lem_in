#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "reader.h"

void	free_all(t_all *all)
{
	t_room	*cursor;
	t_room	*del;
	int		i;

	cursor = all->rooms;
	while (cursor)
	{
		del = cursor;
		cursor = cursor->next;
		free(del->name);
		free(del);
	}
	i = 0;
	while (all->connec && i < all->nb_rooms && all->connec[i])
		free(all->connec[i++]);
	if (all->connec)
		free(all->connec);
	if (all->start)
		free(all->start->name);
	free(all->start);
	if (all->end)
		free(all->end->name);
	free(all->end);
}

void	display_read(t_all *all)
{
	int		i;
	int		j;
	t_room	*cursor;

	ft_printf("nombre de fourmis\t:%d\n", all->nb_ants);
	ft_printf("nombre de salles\t:%d\n", all->nb_rooms);
	cursor = all->start;
	ft_printf("debut\t:%s\tx = %d\ty = %d\n", cursor->name, cursor->x, cursor->y);
	cursor = all->end;
	ft_printf("fin\t:%s\tx = %d\ty = %d\n", cursor->name, cursor->x, cursor->y);
	cursor = all->rooms;
	while (cursor)
	{
		ft_printf("name =%s\tx = %d\ty = %d\n", cursor->name, cursor->x, cursor->y);
		cursor = cursor->next;
	}
	ft_printf("connexions\n");
	j = 0;
	while (j < all->nb_rooms)
	{
		i = 0;
		while (i < all->nb_rooms)
			ft_printf("%4d", all->connec[j][i++]);
		ft_printf("\n");
		j++;
	}
}

int	main(void)
{
	int		fd;
	t_all	all;

	all.nb_ants = 0;
	all.rooms = NULL;
	all.nb_rooms = 0;
	all.connec = NULL;
	all.start = NULL;
	all.end = NULL;
	fd = open("map", O_RDONLY);
	reader(&all, fd);
	close(fd);
	display_read(&all);
	free_all(&all);
	return (1);
}
