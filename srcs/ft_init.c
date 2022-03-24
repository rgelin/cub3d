/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:30:15 by jvander-          #+#    #+#             */
/*   Updated: 2022/03/24 12:43:44 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_struct(t_data *data, t_mlx *mlx)
{
	data->NO_texture_path = NULL;
	data->SO_texture_path = NULL;
	data->WE_texture_path = NULL;
	data->EA_texture_path = NULL;
	data->floor_color = NULL;
	data->roof_color = NULL;
	data->mlx = mlx;
	mlx->screen_width = 1200;
	mlx->screen_heigth = 750;
}

/*
* dirx : 1 pour S - 1 pour N 0 sinon
* diry : -1 pour W, 1 pour E 0 sinon
* planex : -0.66 pour W 0.66 E 0 sinon
* planey : -0.66 pour S 0.66 N 0 sinon
*/
static void	ft_init_raytrack(t_ray *ray, t_data *data)
{
	t_pos	pos_player;

	pos_player = ft_get_pos_player(data->map);
	ray->dirx = -1;
	ray->diry = 0;
	ray->posx = pos_player.x;
	ray->posy = pos_player.y;
	ray->planex = 0.0;
	ray->planey = 0.66;
	ray->movespeed = 0.3;
	ray->rotspeed = 0.4;
	data->ray = ray;
}

static void	ft_create_img(t_mlx *mlx, t_data *data, int text, char *path)
{
	data->texture[text].img_ptr = mlx_xpm_file_to_image(mlx->mlx,
			path, &data->texture[text].width, &data->texture[text].height);
	data->texture[text].data
		= (int *)mlx_get_data_addr(data->texture[text].img_ptr,
			&data->texture[text].bpp,
			&data->texture[text].size_l, &data->texture[text].endian);
}

static void	ft_init_text_window(t_data *data, t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->mlx_window = mlx_new_window(mlx->mlx, mlx->screen_width,
			mlx->screen_heigth, "cub3d");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx, mlx->screen_width,
			mlx->screen_heigth);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr,
			&mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	ft_create_img(mlx, data, NORTH, data->NO_texture_path);
	ft_create_img(mlx, data, WEST, data->WE_texture_path);
	ft_create_img(mlx, data, EAST, data->EA_texture_path);
	ft_create_img(mlx, data, SOUTH, data->SO_texture_path);
}

void	ft_parse_and_init(t_data *data, t_mlx *mlx, t_ray *ray, char *file)
{
	init_struct(data, mlx);
	read_file(file, data);
	if (check_data(data))
		exit (ft_perror("Error: operation file corrupted"));
	split_data(data);
	ft_init_text_window(data, mlx);
	ft_init_raytrack(ray, data);
}
