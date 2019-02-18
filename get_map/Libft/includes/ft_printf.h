/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:48:53 by amerrouc          #+#    #+#             */
/*   Updated: 2019/01/09 14:47:04 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include <limits.h>
# define FD 0

typedef struct	s_flag
{
	int		fd;
	int		alt;
	char	pad;
	int		sign;
	int		min_len;
	int		pre;
	char	mod[3];
	char	conv;
	int		err;
}				t_flag;
typedef int		(*t_fct)(t_flag, va_list);

void			set_base(t_flag *flags, char **base, char *str);
void			apply_padd_str(char *out, const char *str, char *padd,
				t_flag flags);
char			*apply_padd_hex(char *str, char *padd, char *base,
				t_flag flags);
int				skip_spc(char *str, t_flag *flgas, int *count);
int				nb_base_len(unsigned long long int nb, int size_base);
int				ldb_base_len(long double nb, int size_base);
void			put_base(unsigned long long int nb, char *str, char *base);
void			put_dbl(long double nb, char *str, t_flag flags);
char			*ui_long_hex(unsigned long long int nb, int b);
char			*ui_long_oct(unsigned long long int nb, t_flag flags);
t_flag			*set_flags(char *obj, int fd);
char			*pre_str(char *str, t_flag flags);
char			*pre_hex(char *str, t_flag flags);
char			*padd_str(char const *str, t_flag flags);
char			*padd_c(char c, t_flag flags);
char			*lli_str(long long int nb, t_flag flags);
char			*ulli_str(unsigned long long int nbr);
char			*ldb_str(long double nbr, t_flag flags);
int				disp_str(char *str, int *count, int fd);
int				disp_arg(char *str, int *count, va_list ap, t_fct *functions);
int				display(char *str, int *count, va_list ap);
t_fct			*init_functions(void);
int				chose_fct(t_flag *flags);
void			adj_size(long long int *nbr, t_flag flags);
void			adj_prec(long double *nbr, t_flag *flags);
void			adj_uns_size(unsigned long long int *nbr, t_flag flags);
int				len_flags(char *str, t_flag *flags);
int				print_c(t_flag flags, va_list ap);
int				print_s(t_flag flags, va_list ap);
int				print_p(t_flag flags, va_list ap);
int				print_di(t_flag flags, va_list ap);
int				print_hex(t_flag flags, va_list ap);
int				print_o(t_flag flags, va_list ap);
int				print_u(t_flag flags, va_list ap);
int				print_prct(t_flag flags, va_list ap);
int				print_dec(t_flag flags, va_list ap);
char			*padd_hex(char *str, t_flag flags);
int				lib_diff(char *str, char *tmp1, char *tmp2);
void			set_padd_char(char *padd, t_flag flags);
void			cap_conv(t_flag *flags);
int				ft_printf(char *str, ...);
int				ft_dprintf(int fd, char *str, ...);

#endif
