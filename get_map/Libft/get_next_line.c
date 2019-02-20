/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:32:35 by amerrouc          #+#    #+#             */
/*   Updated: 2019/02/20 17:06:16 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lenline(const char *str, size_t size)
{
	size_t	i;

	i = 0;
	while (str[i] && i < size && str[i] != '\n')
		i++;
	return (i);
}

char	*ft_stradd(char **str, char *src, size_t size)
{
	char	*line;
	int		len;

	if (!str[0] || !src[0])
		return (NULL);
	len = ft_strlen(*str);
	if (!(line = ft_strnew(len + size + 1)))
	{
		ft_strdel(str);
		return (NULL);
	}
	ft_memcpy(line, *str, ft_strlen(*str));
	ft_memcpy(line + len, src, size);
	ft_strdel(str);
	return (line);
}

int		rd_cdt(size_t *l, char **line, char **p, int *r)
{
	int		len_ini;
	char	*destr;

	*r = 0;
	if ((!*p) || (!**p))
		return (1);
	len_ini = ft_strlen(*p);
	*l = ft_lenline(*p, len_ini);
	*line = ft_stradd(line, *p, *l);
	if (len_ini == (int)ft_strlen(*line))
	{
		ft_strdel(p);
		return (1);
	}
	destr = *p;
	if (*(*p + (int)*l + 1) == '\0')
		*p = NULL;
	else
		*p = ft_strdup(*p + (int)*l + 1);
	ft_strdel(&destr);
	return (0);
}

int		ret_value(int r, char *p, char *line)
{
	if (r == -1)
		return (r);
	if (!p && !line)
		return (0);
	if (ft_strlen(line) == 0 && r == 0 && p == NULL)
		return (0);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	char		*buffer;
	static char	*p[OPEN_MAX];
	int			r;
	size_t		l;

	if (fd < 0 || fd > OPEN_MAX || !line || !(*line = ft_strnew(1))
		|| BUFF_SIZE < 0 || (!(buffer = ft_strnew(BUFF_SIZE + 1))))
		return (-1);
	if (rd_cdt(&l, line, &p[fd], &r) == 1)
	{
		l = r;
		while (((int)l == r) && ((r = read(fd, buffer, BUFF_SIZE)) > 0))
		{
			l = ft_lenline(buffer, r);
			buffer[r] = '\0';
			if (!(*line = ft_stradd(line, buffer, l)))
				return (-1);
		}
		if (buffer[l] == '\n')
			p[fd] = ft_strdup(buffer + l + 1);
		else
			ft_strdel(&p[fd]);
	}
	ft_strdel(&buffer);
	return (ret_value(r, p[fd], *line));
}
