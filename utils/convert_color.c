/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:54:40 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/22 17:02:39 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	count_nbr(int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		count = 1;
	if (nb < 0)
	{
		nb = -nb;
		count++;
	}
	while (nb > 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*convert_color(char *color_number)
{
	char	*base;
	char	*res;
	int		i;
	int		nbr;

	i = 0;
	nbr = ft_atoi(color_number);
	res = malloc(sizeof(char) * count_nbr(nbr) + 1);
	if (!res)
		return (NULL);
	if (nbr == 0)
		res[i++] = '0';
	base = "0123456789abcdef";
	while (nbr > 0)
	{
		res[i] = base[(nbr % 16)];
		nbr /= 16;
		i++;
	}
	res[i] = '\0';
	ft_swap(res);
	return (res);
}
