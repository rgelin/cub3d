/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:17:09 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/24 16:45:49 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	press_red_cross(t_data *data)
{
	ft_free(data);
	exit(EXIT_SUCCESS);
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

/*
*	ft_free_tab(data.map);
*	ft_free(&data);
*	system("leaks cub3d");
*/
int	main(int ac, char *av[])
{
	t_mlx	mlx;
	t_data	data;
	t_ray	ray;

	if (ac != 2)
		return (ft_perror("Error: argument"));
	check_map_format(av[1]);
	ft_parse_and_init(&data, &mlx, &ray, av[1]);
	mlx_hook(mlx.mlx_window, 17, 1L << 5, press_red_cross, &data);
	mlx_hook(mlx.mlx_window, 2, 0, deal_key, &data);
	mlx_loop_hook(mlx.mlx, ft_ray, &data);
	mlx_loop(mlx.mlx);
	return (0);
}
