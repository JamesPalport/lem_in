/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 10:38:53 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/09 13:06:15 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		disp_str(char *str, int *count, int fd)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '%')
		ft_putchar_fd(str[i++], fd);
	*count += i;
	return (i);
}

int		disp_arg(char *str, int *count, va_list ap, t_fct *functions)
{
	t_flag	*flags;
	int		ch;
	int		len;

	flags = set_flags(str, count[1]);
	ch = chose_fct(flags);
	len = len_flags(str, flags);
	*count += functions[ch](*flags, ap);
	free(flags);
	return (len);
}

int		display(char *str, int *count, va_list ap)
{
	int		i;
	int		ret;
	t_fct	*functions;

	i = 0;
	functions = init_functions();
	while (str[i])
	{
		i = i + disp_str(str + i, &count[0], count[1]);
		if (str[i] == '%')
		{
			if ((ret = disp_arg(str + i + 1, &count[0], ap, functions)) == -1)
				return (-1);
			i = i + 1 + ret;
		}
	}
	free(functions);
	return (1);
}
