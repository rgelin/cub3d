/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:10:34 by jvander-          #+#    #+#             */
/*   Updated: 2022/03/17 13:13:33 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_ray(t_mlx *mlx, t_pos pos_player, t_ray *ray, t_data data)
{
	for (int x = 0; x < mlx->screen_width; x++)
	{
		ray->camerax = 1.5 * x / mlx->screen_width - 1;
		ray->raydirx = ray->dirx + ray->planex * ray->camerax;
		ray->raydiry = ray->diry + ray->planey * ray->camerax;
		ray->mapx = pos_player.x;
		ray->mapy = pos_player.y;
		ray->deltadistx = fabs(1 / ray->raydirx);
		ray->deltadisty = fabs(1 / ray->raydiry);
		ray->hit = 0;
		if (ray->raydirx < 0)
		{
			ray->stepx = -1;
			ray->sidedistx = (pos_player.x - ray->mapx) * ray->deltadistx;
		}
		else
		{
			ray->stepx = 1;
			ray->sidedistx = (ray->mapx + 1.0 - pos_player.x) * ray->deltadistx;
		}
		if (ray->raydiry < 0)
		{
			ray->stepy = -1;
			ray->sidedisty = (pos_player.y - ray->mapy) * ray->deltadisty;
		}
		else
		{
			ray->stepy = 1;
			ray->sidedisty = (ray->mapy + 1.0 - pos_player.y) * ray->deltadisty;
		}
		while (ray->hit == 0)
		{
			if (ray->sidedistx < ray->sidedisty)
			{
				ray->sidedistx += ray->deltadistx;
				ray->mapx += ray->stepx;
				ray->side = 0;
			}
			else
			{
				ray->sidedisty += ray->deltadisty;
				ray->mapy += ray->stepy;
				ray->side = 1;
			}
			if (data.map[ray->mapx][ray->mapy] == '1')
				ray->hit = 1;
		}
		if (ray->side == 0)
			ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
		else
			ray->perpwalldist = (ray->sidedisty - ray->deltadisty);
		ray->lineheight = mlx->screen_heigth / ray->perpwalldist;
		ray->drawstart = -ray->lineheight / 2 + mlx->screen_heigth / 2;
		if (ray->drawstart < 0)
			ray->drawstart = 0;
		ray->drawend = ray->lineheight / 2 + mlx->screen_heigth / 2;
		if (ray->drawend >= mlx->screen_heigth)
			ray->drawend = mlx->screen_heigth - 1;
		int y = ray->drawstart;
		while (y < ray->drawend)
		{
			int color = 0xf2f2f2;;
			if (ray->side == 1)
				color = 0xCCCCCC;
			mlx->img.data[y * mlx->img.size_l / 4 + x] = color;
			y++;
		}
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
}