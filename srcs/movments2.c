/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movments2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:01:25 by jvander-          #+#    #+#             */
/*   Updated: 2022/03/22 15:31:18 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_rotate_left(t_data *data)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->ray->dirx;
	oldplanex = data->ray->planex;
	data->ray->dirx = data->ray->dirx * cos(data->ray->rotspeed / 2)
		- data->ray->diry * sin(data->ray->rotspeed / 2);
	data->ray->diry = olddirx * sin(data->ray->rotspeed / 2)
		+ data->ray->diry * cos(data->ray->rotspeed / 2);
	data->ray->planex = data->ray->planex * cos(data->ray->rotspeed / 2)
		- data->ray->planey * sin(data->ray->rotspeed / 2);
	data->ray->planey = oldplanex * sin(data->ray->rotspeed / 2)
		+ data->ray->planey * cos(data->ray->rotspeed / 2);
}
