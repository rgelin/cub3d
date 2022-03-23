/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayTracking_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:21:50 by jvander-          #+#    #+#             */
/*   Updated: 2022/03/23 17:43:31 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_draw_wall(t_ray *ray, t_mlx *mlx, int x, t_data *data)
{
	int	y;
	int	color;
	// int	tex_num = data->map[data->ray->mapx][data->ray->mapy] - 1;
	double	wall_x;
	
	if (ray->side == 0)
		wall_x = ray->posy + ray->perpwalldist * ray->raydiry;
	else
		wall_x = ray->posx + ray->perpwalldist * ray->raydirx;
	wall_x -= floorf((wall_x));
	int tex_x = (int)(wall_x * (double)data->texture[0].width);
	if (ray->side == 0 && ray->raydirx > 0)
		tex_x = data->texture[0].width - tex_x - 1;
	if (ray->side == 1 && ray->raydiry < 0)
		tex_x = data->texture[0].width - tex_x - 1;
	double step = 1.0 * data->texture[0].height / ray->lineheight;
	double tex_pos = (ray->drawstart - mlx->screen_heigth / 2
		+ ray->lineheight / 2) * step;

	y = ray->drawstart;
	while (y < ray->drawend)
	{
		int tex_y = (int)tex_pos & (data->texture[0].height - 1);
		tex_pos += step;
		if (y < mlx->screen_heigth && x < mlx->screen_width)
		{
			mlx->img.data[y * mlx->img.size_l / 4 + x] =
				data->texture[0].data[tex_y * data->texture[0].size_l / 4 + tex_x];
		}
		// color = 0xf2f2f2;
		// if (ray->side == 1)
		// 	color = 0xCCCCCC;
		// mlx->img.data[y * mlx->img.size_l / 4 + x] = color;
		y++;
	}
}

void	ft_draw_floor_roof(t_ray *ray, t_mlx *mlx, int x)
{
	int	y;

	if (ray->drawend < 0)
		ray->drawend = mlx->screen_heigth;
	y = ray->drawend;
	while (y < mlx->screen_heigth)
	{
		mlx->img.data[y * mlx->img.size_l / 4 + x] = 0xCC6600;
		y++;
	}
	y = ray->drawstart;
	while (y >= 0)
	{
		mlx->img.data[y * mlx->img.size_l / 4 + x] = 0x00FFFF;
		y--;
	}
}
