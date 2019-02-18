/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 09:26:44 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/09 11:12:57 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_prct(t_flag flags, va_list ap)
{
	char	str[2];
	char	*tmp;
	int		len;

	(void)ap;
	str[0] = flags.conv;
	str[1] = '\0';
	flags.err = 1;
	tmp = str;
	if (!(tmp = padd_str(tmp, flags)))
		return (lib_diff(str, tmp, tmp));
	ft_putstr_fd(tmp, flags.fd);
	len = ft_strlen(tmp);
	lib_diff(str, tmp, tmp);
	return (len);
}
