/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 16:08:36 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/13 17:31:20 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && (s[i] != c))
			i++;
		count++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

static int	wrdlen(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i + len] && s[i + len] != c)
		len++;
	return (len);
}

static void	wrdcpy(char const *s, char c, char **out)
{
	int	i;
	int	cwrd;
	int	len;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	cwrd = 0;
	while (s[i])
	{
		len = wrdlen(s, c, i);
		out[cwrd] = ft_strsub(s, (unsigned int)i, (size_t)len + 1);
		i += len;
		out[cwrd][len] = '\0';
		cwrd++;
		while (s[i] && s[i] == c)
			i++;
	}
	out[cwrd] = 0;
}

char		**ft_strsplit(char const *s, char c)
{
	int		cwrd;
	char	**out;

	if (s)
	{
		cwrd = count_word(s, c);
		if ((out = (char **)malloc(sizeof(char *) * (cwrd + 1))) == 0)
			return (NULL);
		wrdcpy(s, c, out);
		return (out);
	}
	return (NULL);
}
