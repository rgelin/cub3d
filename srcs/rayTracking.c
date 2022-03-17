/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:10:34 by jvander-          #+#    #+#             */
/*   Updated: 2022/03/17 13:26:29 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_init_ray(t_ray *ray, t_pos pos_player, t_mlx *mlx, int x)
{
	ray->camerax = 1.5 * x / mlx->screen_width - 1;
	ray->raydirx = ray->dirx + ray->planex * ray->camerax;
	ray->raydiry = ray->diry + ray->planey * ray->camerax;
	ray->mapx = pos_player.x;
	ray->mapy = pos_player.y;
	ray->deltadistx = fabs(1 / ray->raydirx);
	ray->deltadisty = fabs(1 / ray->raydiry);
	ray->hit = 0;
}

static void	ft_calc_initial_side_dist(t_ray *ray, t_pos pos_player)
{
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
}

static void	ft_calc_dist_wall(t_data data, t_ray *ray)
{
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
}

static void	ft_calc_begin_end(t_ray *ray, t_mlx *mlx)
{
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
}

void	ft_ray(t_mlx *mlx, t_pos pos_player, t_ray *ray, t_data data)
{
	int	x;

	x = -1;
	while (++x < mlx->screen_width)
	{
		ft_init_ray(ray, pos_player, mlx, x);
		ft_calc_initial_side_dist(ray, pos_player);
		ft_calc_dist_wall(data, ray);
		ft_calc_begin_end(ray, mlx);
		ft_draw_wall(ray, mlx, x);
		ft_draw_floor_roof(ray, mlx, x);
	}
}
