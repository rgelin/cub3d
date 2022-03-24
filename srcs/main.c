/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:17:09 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/24 12:05:47 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	press_red_cross(t_data *data)
{
	ft_free(data);
	// system("leaks cub3d");
	exit(EXIT_SUCCESS);
}

void	init_struct(t_data *data, t_mlx *mlx)
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
* W = 13, S = 1, D = 2, A = 0, ARROW LEFT = 123, ARROW RIGHT = 124
*/
int	deal_key(int key_code, t_data *data)
{
	t_pos	pos_p;

	pos_p = ft_get_pos_player(data->map);
	if (key_code == 53)
		exit(0);
	if (key_code == 13)
		ft_move_up(data);
	if (key_code == 1)
		ft_move_down(data);
	if (key_code == 2)
		ft_move_right(data);
	if (key_code == 0)
		ft_move_left(data);
	if (key_code == 123)
		ft_rotate_left(data);
	if (key_code == 124)
		ft_rotate_right(data);
	return (0);
}

int	main(int ac, char *av[])
{
	t_mlx	mlx;
	t_data	data;
	t_ray	ray;
	t_pos	pos_player;

	if (ac != 2)
		return (ft_perror("Error: argument"));
	check_map_format(av[1]);
	init_struct(&data, &mlx);
	read_file(av[1], &data);
	if (check_data(&data))
		return (ft_perror("Error: operation file corrupted"));
	split_data(&data);
	mlx.mlx = mlx_init();
	mlx.mlx_window = mlx_new_window(mlx.mlx, mlx.screen_width,
			mlx.screen_heigth, "cub3d");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx, mlx.screen_width,
			mlx.screen_heigth);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr,
			&mlx.img.bpp, &mlx.img.size_l, &mlx.img.endian);
	pos_player = ft_get_pos_player(data.map);
	ray.dirx = -1; // 1 pour S - 1 pour N 0 sinon
	ray.diry = 0; // -1 pour W, 1 pour E 0 sinon
	ray.posx = pos_player.x;
	ray.posy = pos_player.y;
	ray.planex = 0.0; // -0.66 pour W 0.66 E 0 sinon
	ray.planey = 0.66; // -0.66 pour S 0.66 N 0 sinon
	ray.movespeed = 0.3;
	ray.rotspeed = 0.4;
	data.texture[NORTH].img_ptr = mlx_xpm_file_to_image(mlx.mlx,
		data.NO_texture_path, &data.texture[NORTH].width,
		&data.texture[NORTH].height);
	data.texture[NORTH].data = (int *)mlx_get_data_addr(data.texture[NORTH].img_ptr,
		&data.texture[NORTH].bpp, &data.texture[NORTH].size_l, &data.texture[NORTH].endian);
	data.texture[SOUTH].img_ptr = mlx_xpm_file_to_image(mlx.mlx,
		data.SO_texture_path, &data.texture[SOUTH].width,
		&data.texture[SOUTH].height);
	data.texture[SOUTH].data = (int *)mlx_get_data_addr(data.texture[SOUTH].img_ptr,
		&data.texture[SOUTH].bpp, &data.texture[SOUTH].size_l, &data.texture[SOUTH].endian);
	data.texture[EAST].img_ptr = mlx_xpm_file_to_image(mlx.mlx,
		data.EA_texture_path, &data.texture[EAST].width,
		&data.texture[EAST].height);
	data.texture[EAST].data = (int *)mlx_get_data_addr(data.texture[EAST].img_ptr,
		&data.texture[EAST].bpp, &data.texture[EAST].size_l, &data.texture[EAST].endian);
	data.texture[WEST].img_ptr = mlx_xpm_file_to_image(mlx.mlx,
		data.WE_texture_path, &data.texture[WEST].width,
		&data.texture[WEST].height);
	data.texture[WEST].data = (int *)mlx_get_data_addr(data.texture[WEST].img_ptr,
		&data.texture[WEST].bpp, &data.texture[WEST].size_l, &data.texture[WEST].endian);
	
	data.ray = &ray;
	ft_ray(&data);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_window, mlx.img.img_ptr, 0, 0);
	mlx_hook(mlx.mlx_window, 17, 1L << 5, press_red_cross, &data);
	mlx_hook(mlx.mlx_window, 2, 0, deal_key, &data);
	mlx_loop_hook(mlx.mlx, ft_ray, &data);
	mlx_loop(mlx.mlx);
	// ft_free_tab(data.map);
	// ft_free(&data);
	// system("leaks cub3d");
	return (0);
}
