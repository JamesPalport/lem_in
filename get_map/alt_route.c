/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_route.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:47:53 by amerrouc          #+#    #+#             */
/*   Updated: 2019/03/14 16:08:51 by amerrouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "reader.h"

static int	*ft_intnew(int len)
{
	int	*new;

	if (!(new = (int *)malloc(sizeof(int) * len)))
		return (NULL);
	while (len--)
		new[len] = 0;
	return (new);
}

void		dispatch_route(t_routes *route1, t_routes *route2, int room)
{
	int	i;
	int	j;
	int	*new1;
	int	*new2;
	int	n;

	i = 0;
	while (i < route1->len && route1->path[i] != room)
		i++;
	j = 0;
	while (j < route2->len && route2->path[j + 1] != room)
		j++;
	if (i == route1->len || j == route2->len)
		return ;
	if (!(new1 = ft_intnew(i + route2->len - j))
			|| !(new2 = ft_intnew(j + route1->len - i)))
		return ;
	n = -1;
	while (++n < i)
		new1[n] = route1->path[n];
	n = -1;
	while (++n + j < route2->len)
		new1[i + n] = route2->path[j + n];
	n = -1;
	while (++n < j + 1)
		new2[n] = route2->path[n];
	n = -1;
	while (++n + i < route1->len)
		new1[j + n] = route1->path[i + n];


}
