/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayTracking_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:21:50 by jvander-          #+#    #+#             */
/*   Updated: 2022/03/24 12:12:40 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_get_orientation(t_ray *ray)
{
	if (ray->side == 1)
	{
		if (ray->mapy - ray->posy > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (ray->mapx - ray->posx > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
	return (-1);
}

static void	ft_get_info_tex(t_tex *tex, t_data *data, t_ray *ray, t_mlx *mlx)
{
	tex->tex_num = ft_get_orientation(ray);
	if (data->ray->side == 0)
		tex->wall_x = ray->posy + ray->perpwalldist * ray->raydiry;
	else
		tex->wall_x = ray->posx + ray->perpwalldist * ray->raydirx;
	tex->wall_x -= floor((tex->wall_x));
	tex->tex_x = (int)(tex->wall_x * (double)data->texture[tex->tex_num].width);
	if (ray->side == 0 && ray->raydirx > 0)
		tex->tex_x = data->texture[tex->tex_num].width - tex->tex_x - 1;
	if (ray->side == 1 && ray->raydiry < 0)
		tex->tex_x = data->texture[tex->tex_num].width - tex->tex_x - 1;
	tex->step = 1.0 * data->texture[tex->tex_num].height / ray->lineheight;
	tex->tex_pos = (ray->drawstart - mlx->screen_heigth / 2
			+ ray->lineheight / 2) * tex->step;
}

void	ft_draw_wall(t_ray *ray, t_mlx *mlx, int x, t_data *data)
{
	int		y;
	t_tex	tex;

	ft_get_info_tex(&tex, data, ray, mlx);
	y = ray->drawstart;
	while (y < ray->drawend)
	{
		tex.tex_y = (int)tex.tex_pos & (data->texture[tex.tex_num].height - 1);
		tex.tex_pos += tex.step;
		if (y < mlx->screen_heigth && x < mlx->screen_width)
		{
			mlx->img.data[y * mlx->img.size_l / 4 + x]
				= data->texture[tex.tex_num].data[tex.tex_y
				* data->texture[tex.tex_num].size_l / 4 + tex.tex_x];
		}
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
