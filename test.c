#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "reader.h"

void	free_all(t_all *all)
{
	t_room	*cursor;
	t_room	*del;
	t_routes	*del_routes;
	t_routes	*cursor_routes;
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
	del_routes = all->routes;
	while (del_routes)
	{
		cursor_routes = del_routes;
		free(del_routes->path);
		del_routes = del_routes->next;
		free(cursor_routes);
	}
	if (all->connec)
		free(all->connec);
	if (all->start)
		free(all->start->name);
	free(all->start);
	if (all->end)
		free(all->end->name);
	free(all->end);
}

static char	*get_name(t_all *all, int num)
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
	if ((cursor = all->start) != NULL)
	ft_printf("debut\t:%s\tx = %d\ty = %d\n", cursor->name, cursor->x, cursor->y);
	if ((cursor = all->end) != NULL)
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
	int			*pt;

	cursor = all->routes;
	ft_putendl("routes");
	while (cursor)
	{
		i = 0;
		pt = cursor->path;
		while (i < cursor->len)
		{
			ft_printf("%s->", get_name(all, pt[i]));
			i++;
		}
		ft_printf("%s\n", get_name(all, pt[i]));
		cursor = cursor->next;
	}
}

void	display_select(t_all *all)
{
	int			j;
	t_routes	*cursor;
	int			i;
	int			*pt;

	j = 0;
	ft_putendl("selected");
	while (all->select[j])
	{
		i = 0;
		cursor = all->select[j];
		pt = cursor->path;
		while (i < cursor->len)
		{
			ft_printf("%s->", get_name(all, pt[i]));
			i++;
		}
		ft_printf("%s\n", get_name(all, pt[i]));
		cursor = cursor->next;
		j++;
	}
}

#include <time.h>

int	main(int argc, char **argv)
{
	int		fd;
	t_all	all;
	char	*name;
	t_tmpr	tmp_routes;

	all.nb_ants = 0;
	all.rooms = NULL;
	all.nb_rooms = 0;
	all.connec = NULL;
	all.start = NULL;
	all.end = NULL;
	all.routes = NULL;
	all.score = NULL;
	all.max_score = 0;
	all.select = NULL;
	tmp_routes.to_vis = NULL;
	tmp_routes.new_vis = NULL;
	if (argc > 1)
		name = argv[argc - 1];
	else
		name = "map";
	fd = open(name, O_RDONLY);
	if (!reader(&all, fd) || !check_map(&all))
	{
		close(fd);
		free_all(&all);
		ft_putendl("map error");
		return (0);
	}
	close(fd);
//	display_read(&all);
	bfs(&all, -1, &tmp_routes);
	get_routes(&all);;
	all.routes = order_routes(all.routes);
//	display_routes(&all);
	bfs(&all, all.max_score + all.routes->len, &tmp_routes);
	get_routes(&all);
	all.routes = order_routes(all.routes);
	display_routes(&all);
	chose_route(&all);
	display_routes(&all);
	display_select(&all);
	move_ants(&all);
	free_all(&all);
	free(tmp_routes.to_vis);
	free(tmp_routes.new_vis);
	return (1);
}
