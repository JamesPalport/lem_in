/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 09:40:24 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/09 11:29:24 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flag	*new_flags(void)
{
	t_flag	*new;

	if ((new = (t_flag *)malloc(sizeof(t_flag))) == 0)
		return ((t_flag *)0);
	new->fd = 1;
	new->alt = 0;
	new->pad = 0;
	new->sign = 0;
	new->min_len = -1;
	new->pre = -1;
	new->mod[0] = 0;
	new->mod[1] = 0;
	new->mod[2] = 0;
	new->conv = 0;
	new->err = 0;
	return (new);
}

void	fl_1(char c, t_flag *new)
{
	if (c == '#')
		new->alt = 1;
	if (c == '+')
		new->sign = 2;
	if (c == ' ' && new->sign != 2)
		new->sign = 1;
	if (c == '0' && new->pad == 0)
		new->pad = '0';
	if (c == '-')
		new->pad = ' ';
}

void	fl_2(char *c, t_flag *new)
{
	if (*c == 'l' || *c == 'h' || *c == 'L')
	{
		if (new->mod[0] == 0)
			new->mod[0] = *c;
		else if (new->mod[0] == *c && new->mod[1] == 0)
			new->mod[1] = *c;
		else
			new->err = 1;
		if (new->err)
			new->conv = *(++c);
	}
	else
		new->conv = *c;
}

void	fl_3(char *obj, int *i, t_flag *new)
{
	if (obj[*i] == '.' && new->pre == -1)
	{
		*i += 1;
		new->pre = ft_atoi(obj + *i);
		while (ft_isdigit(obj[*i + 1]))
			*i += 1;
	}
	if (ft_isdigit(obj[*i]) && obj[*i] != '0' && new->pre == -1)
	{
		if (new->min_len == -1)
			new->min_len = ft_atoi(obj + *i);
		while (ft_isdigit(obj[*i + 1]))
			*i += 1;
	}
}

t_flag	*set_flags(char *obj, int fd)
{
	t_flag	*new;
	int		i;

	new = new_flags();
	i = 0;
	new->fd = fd;
	while (obj[i] && new->err == 0 && new->conv == 0)
	{
		fl_3(obj, &i, new);
		if (new->min_len == -1 && new->pre == -1)
			fl_1(obj[i], new);
		else if (obj[i] == '#' || obj[i] == '+'
				|| obj[i] == ' ' || obj[i] == '-' || obj[i] == '%')
			new->err = 1;
		if (!ft_isdigit(obj[i]) && obj[i] != '.' && obj[i] != '-'
				&& obj[i] != '+' && obj[i] != ' ' && obj[i] != '#')
			fl_2(obj + i, new);
		i++;
	}
	return (new);
}
