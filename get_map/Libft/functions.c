/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 11:24:51 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/07 14:03:06 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fct	*init_functions(void)
{
	t_fct	*functions;

	if (!(functions = (t_fct *)malloc(sizeof(t_fct) * 9)))
		return (NULL);
	functions[0] = &print_c;
	functions[1] = &print_s;
	functions[2] = &print_p;
	functions[3] = &print_di;
	functions[4] = &print_o;
	functions[5] = &print_u;
	functions[6] = &print_hex;
	functions[7] = &print_dec;
	functions[8] = &print_prct;
	return (functions);
}
