/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:17:09 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/19 16:33:49 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	press_red_cross(t_mlx *mlx)
{
	ft_free(mlx->data);
	// system("leaks cub3d");
	exit(EXIT_SUCCESS);
}


void init_struct(t_data *data, t_mlx *mlx)
{
	data->NO_texture_path = NULL;
	data->SO_texture_path = NULL;
	data->WE_texture_path = NULL;
	data->EA_texture_path = NULL;
	data->floor_color = NULL;
	data->roof_color = NULL;

	mlx->data = data;
	mlx->screen_heigth = 800;
	mlx->screen_width = 800;
}

/*
* W = 13, S = 1, D = 2, A = 0
*/
int		deal_key(int key_code, t_data *data)
{
	(void)data;
	if (key_code == 53)
		exit(0);
	if (key_code == 13)
	{
		printf("W\n");
		return (13);
	}
	if (key_code == 1)
	{
		printf("S\n");
		return (1);
	}
	if (key_code == 2)
	{
		printf("D\n");
		return (2);
	}
	if (key_code == 0)
	{
		printf("A\n");
		return (0);
	}
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
	mlx.mlx_window = mlx_new_window(mlx.mlx, mlx.screen_width, mlx.screen_heigth, "cub3d");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx, mlx.screen_width, mlx.screen_heigth);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l,
		&mlx.img.endian);
		
	pos_player = ft_get_pos_player(data.map);
	ray.dirx = -1;
	ray.diry = 0;
	ray.planex = 0;
	ray.planey = 0.66;
	ft_ray(&mlx, pos_player, &ray, data);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_window, mlx.img.img_ptr, 0, 0);
	mlx_hook(mlx.mlx_window, 17, 1L << 5, press_red_cross, &mlx);
	mlx_hook(mlx.mlx_window, 2, 0, deal_key, &mlx);
	mlx_loop(mlx.mlx);
	// ft_free_tab(data.map);
	// ft_free(&data);
	// system("leaks cub3d");
	return (0);
}
