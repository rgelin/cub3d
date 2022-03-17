/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayTracking_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:21:50 by jvander-          #+#    #+#             */
/*   Updated: 2022/03/17 13:27:25 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_draw_wall(t_ray *ray, t_mlx *mlx, int x)
{
	int	y;
	int	color;

	y = ray->drawstart;
	while (y < ray->drawend)
	{
		color = 0xf2f2f2;
		if (ray->side == 1)
			color = 0xCCCCCC;
		mlx->img.data[y * mlx->img.size_l / 4 + x] = color;
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
