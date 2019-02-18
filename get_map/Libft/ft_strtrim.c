/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 14:00:33 by amerrouc          #+#    #+#             */
/*   Updated: 2018/11/18 15:26:46 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_start(char const *s)
{
	unsigned int	start;
	int				c;

	c = 0;
	start = 0;
	while ((c == 0) && s[start])
	{
		c = 1;
		if (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
			c = 0;
		if (c == 0)
			start++;
	}
	c = 0;
	return (start);
}

static unsigned int	ft_end(char const *s)
{
	unsigned int	end;
	int				c;

	end = ft_strlen(s);
	c = 0;
	end--;
	while ((c == 0) && end)
	{
		c = 1;
		if (s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
			c = 0;
		if (c == 0)
			end--;
	}
	return (end);
}

char				*ft_strtrim(char const *s)
{
	unsigned int	start;
	unsigned int	end;
	char			*out;

	if (s)
	{
		if (ft_strlen(s))
		{
			start = ft_start(s);
			end = ft_end(s);
			if (end == 0)
				start = end + 1;
			out = ft_strsub(s, start, (size_t)(end - start + 1));
			return (out);
		}
		else
			return ((char *)s);
	}
	return (NULL);
}
