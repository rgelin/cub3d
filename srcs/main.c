/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:17:09 by rgelin            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/17 11:32:23 by jvander-         ###   ########.fr       */
=======
/*   Updated: 2022/03/16 13:35:19 by jvander-         ###   ########.fr       */
>>>>>>> d5527f3c97395014ffb28c6cfe7325696177d28c
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
	mlx->screen_heigth = 1080;
	mlx->screen_width = 1080;
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
	t_data data;
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
	mlx_hook(mlx.mlx_window, 17, 1L << 5, press_red_cross, &mlx);
	mlx_loop(mlx.mlx);
	// ft_free_tab(data.map);
	// ft_free(&data);
	// system("leaks cub3d");
	return (0);
}
