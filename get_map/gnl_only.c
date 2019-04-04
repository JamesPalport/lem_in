#include "Libft/includes/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	char	*line;
	int		fd;

	fd = open(argv[argc - 1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		ft_putendl(line);
	ft_putendl(line);
	close(fd);
	return (1);
}
