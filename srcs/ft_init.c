/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:30:15 by jvander-          #+#    #+#             */
/*   Updated: 2022/03/30 15:56:40 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_struct(t_data *data, t_mlx *mlx)
{
	data->no_texture_path = NULL;
	data->so_texture_path = NULL;
	data->we_texture_path = NULL;
	data->ea_texture_path = NULL;
	data->floor_color = NULL;
	data->roof_color = NULL;
	data->mlx = mlx;
	mlx->screen_width = 1200;
	mlx->screen_heigth = 750;
	data->texture[0].data = 0;
	data->texture[1].data = 0;
	data->texture[2].data = 0;
	data->texture[3].data = 0;
	data->mlx->mlx = NULL;
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
	ray->posx = pos_player.x + 0.5;
	ray->posy = pos_player.y + 0.5;
	ft_determine_start_orientation(data, ray);
	ray->movespeed = 0.4;
	ray->rotspeed = 0.4;
	data->ray = ray;
}

static void	ft_create_img(t_mlx *mlx, t_data *data, int text, char *path)
{
	data->texture[text].img_ptr = mlx_xpm_file_to_image(mlx->mlx,
			path, &data->texture[text].width, &data->texture[text].height);
	if (!data->texture[text].img_ptr)
		ft_perror("Error: XPM file to image", data);
	data->texture[text].data
		= (int *)mlx_get_data_addr(data->texture[text].img_ptr,
			&data->texture[text].bpp,
			&data->texture[text].size_l, &data->texture[text].endian);
}

static void	ft_init_text_window(t_data *data, t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		ft_perror("Error: MLX init", data);
	mlx->mlx_window = mlx_new_window(mlx->mlx, mlx->screen_width,
			mlx->screen_heigth, "cub3d");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx, mlx->screen_width,
			mlx->screen_heigth);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr,
			&mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	ft_create_img(mlx, data, NORTH, data->no_texture_path);
	ft_create_img(mlx, data, WEST, data->we_texture_path);
	ft_create_img(mlx, data, EAST, data->ea_texture_path);
	ft_create_img(mlx, data, SOUTH, data->so_texture_path);
}

void	ft_parse_and_init(t_data *data, t_mlx *mlx, t_ray *ray, char *file)
{
	read_file(file, data);
	if (check_data(data))
		ft_perror("Error: operation file corrupted", data);
	split_data(data);
	ft_init_text_window(data, mlx);
	ft_init_raytrack(ray, data);
}
