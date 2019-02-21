#include "Libft/includes/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main(int argc, const char *argv[])
{
	int	fd;
	char	*line;

	fd = open("map", O_RDONLY);
	while (get_next_line(fd, &line))
		free(line);
	free(line);
	return 0;
}
