/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:36:48 by jvander-          #+#    #+#             */
/*   Updated: 2022/03/22 15:30:36 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_move_up(t_data *data)
{
	if (data->map[(int)(data->ray->posx + (data->ray->dirx
				* data->ray->movespeed * 2))][(int)data->ray->posy] != '1')
		data->ray->posx += data->ray->dirx * data->ray->movespeed;
	if (data->map[(int)(data->ray->posx)][(int)(data->ray->posy +
				(data->ray->diry * data->ray->movespeed * 2))] != '1')
		data->ray->posy += data->ray->diry * data->ray->movespeed;
}

void	ft_move_left(t_data *data)
{
	if (data->map[(int)(data->ray->posx - data->ray->diry
			* (data->ray->movespeed * 2))][(int)data->ray->posy] != '1')
		data->ray->posx -= data->ray->diry * data->ray->movespeed;
	if (data->map[(int)data->ray->posx][(int)(data->ray->posy
		+ data->ray->dirx * (data->ray->movespeed * 2))] != '1')
		data->ray->posy += data->ray->dirx * data->ray->movespeed;
}

void	ft_move_right(t_data *data)
{
	if (data->map[(int)(data->ray->posx + data->ray->diry * (data
				->ray->movespeed * 2))][(int)data->ray->posy] != '1')
		data->ray->posx += data->ray->diry * data->ray->movespeed;
	if (data->map[(int)data->ray->posx][(int)(data->ray->posy
		- data->ray->dirx * (data->ray->movespeed * 2))] != '1')
		data->ray->posy -= data->ray->dirx * data->ray->movespeed;
}

void	ft_move_down(t_data *data)
{
	if (data->map[(int)(data->ray->posx - (data->ray->dirx * data
				->ray->camerax * 2))][(int)(data->ray->posy)] != '1')
		data->ray->posx -= data->ray->dirx * data->ray->movespeed;
	if (data->map[(int)(data->ray->posx)][(int)(data->ray->posy -
				(data->ray->diry * data->ray->movespeed * 2))] != '1')
		data->ray->posy -= data->ray->diry * data->ray->movespeed;
}

void	ft_rotate_right(t_data *data)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->ray->dirx;
	oldplanex = data->ray->planex;
	data->ray->dirx = data->ray->dirx * cos(-data->ray->rotspeed / 2)
		- data->ray->diry * sin(-data->ray->rotspeed / 2);
	data->ray->diry = olddirx * sin(-data->ray->rotspeed / 2)
		+ data->ray->diry * cos(-data->ray->rotspeed / 2);
	data->ray->planex = data->ray->planex * cos(-data->ray->rotspeed / 2)
		- data->ray->planey * sin(-data->ray->rotspeed / 2);
	data->ray->planey = oldplanex * sin(-data->ray->rotspeed / 2)
		+ data->ray->planey * cos(-data->ray->rotspeed / 2);
}
