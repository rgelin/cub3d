/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:54:40 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/31 16:07:25 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

long	convert_color(char *color, t_data *data)
{
	int		r;
	int		g;
	int		b;
	char	**split;

	split = ft_split(color, ',');
	if (!split)
		ft_perror("Error: malloc", data);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	ft_free_tab(split);
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}
