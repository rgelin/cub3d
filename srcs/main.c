/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:17:09 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/14 15:01:09 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	press_red_cross(t_data *data)
{
	(void)data;
	ft_free(data);
	exit(EXIT_SUCCESS);
}

int	press_escape(t_data *data)
{
	ft_free(data);
	mlx_destroy_window(data->mlx, data->mlx_window);
	exit (EXIT_SUCCESS);
}

void init_struct(t_data *data)
{
	data->NO_texture_path = NULL;
	data->SO_texture_path = NULL;
	data->WE_texture_path = NULL;
	data->EA_texture_path = NULL;
	data->floor_color = NULL;
	data->roof_color = NULL;
}

int	main(int ac, char *av[])
{
	t_data data;
	t_pos	pos_player;

	if (ac != 2)
		return (ft_perror("Error: argument"));
	data.file_path = av[1];
	check_map_format(av[1]);
	init_struct(&data);
	read_file(av[1], &data);
	if (check_data(&data))
		return (ft_perror("Error: operation file corrupted"));
	split_data(&data);
	pos_player = ft_get_pos_player(data.map);
	data.mlx = mlx_init();
	data.mlx_window = mlx_new_window(data.mlx, 800, 800, "cub3d");
	mlx_hook(data.mlx_window, 17, 1L << 5, press_red_cross, &data.mlx);
	mlx_loop(data.mlx);
	// ft_free_tab(data.map);
	// ft_free(&data);
	// system("leaks cub3d");
	return (0);
}