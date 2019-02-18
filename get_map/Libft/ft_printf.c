/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 10:13:32 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/09 13:06:17 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(char *str, ...)
{
	va_list	ap;
	int		i;
	int		count[2];
	t_fct	*functions;
	int		ret;

	va_start(ap, str);
	functions = init_functions();
	i = 0;
	count[0] = 0;
	count[1] = 1;
	while (str[i])
	{
		i = i + disp_str(str + i, &count[0], 1);
		if (str[i] == '%')
		{
			if ((ret = disp_arg(str + i + 1, &count[0], ap, functions)) == -1)
				return (-1);
			i = i + 1 + ret;
		}
	}
	free(functions);
	va_end(ap);
	return (count[0]);
}

int	ft_dprintf(int fd, char *str, ...)
{
	va_list	ap;
	int		count[2];

	if (fd < 0 || fd > OPEN_MAX)
		return (-1);
	va_start(ap, str);
	count[0] = 0;
	count[1] = fd;
	if (display(str, count, ap) == -1)
		return (-1);
	va_end(ap);
	return (count[0]);
}
