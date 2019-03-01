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

char	*get_name(t_all *all, int num)
{
	int		i;
	t_room	*cursor;

	i = 1;
	if (num == 0)
		return (all->start->name);
	if (num == all->nb_rooms - 1)
		return (all->end->name);
	cursor = all->rooms;
	while (i++ != num)
		cursor = cursor->next;
	return (cursor->name);
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

void	display_routes(t_all *all)
{
	t_routes	*cursor;
	int			i;
	char		*pt;

	cursor = all->routes;
	ft_putendl("routes");
	while (cursor)
	{
		i = 0;
		pt = cursor->path;
		while (pt[i])
		{
			ft_printf("%s->", get_name(all, ft_atoi(pt + i)));
			while (pt[i] != '.')
				i++;
			i++;
		}
		ft_putstr("\n");
		cursor = cursor->next;
	}
}

int	main(int argc, char **argv)
{
	int		fd;
	t_all	all;
	char	*name;

	all.nb_ants = 0;
	all.rooms = NULL;
	all.nb_rooms = 0;
	all.connec = NULL;
	all.start = NULL;
	all.end = NULL;
	all.routes = NULL;
	if (argc > 1)
		name = argv[argc - 1];
	else
		name = "map";
	fd = open(name, O_RDONLY);
	reader(&all, fd);
	close(fd);
	display_read(&all);
	ft_putstr("\n");
	get_routes(&all);
	display_routes(&all);
	free_all(&all);
	return (1);
}
