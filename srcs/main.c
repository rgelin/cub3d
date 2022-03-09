/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:17:09 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/09 18:09:02 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	press_red_cross(t_mlx *mlx)
{
	(void)mlx;
	// destroy_image(mlx);
	// mlx_destroy_window(mlx->mlx, mlx->mlx_window);
	exit(EXIT_SUCCESS);
}

int	check_map(char *str)
{
	
}

int	main(int ac, char *av[])
{
	(void)ac;
	(void)av;
	t_mlx mlx;

	if (ac != 2)
		exit(EXIT_FAILURE);
	mlx.mlx = mlx_init();
	mlx.mlx_window = mlx_new_window(mlx.mlx, 800, 800, "cub3d");
	mlx_hook(mlx.mlx_window, 17, 1L << 5, press_red_cross, &mlx);
	mlx_loop(mlx.mlx);
	exit(EXIT_SUCCESS);
}