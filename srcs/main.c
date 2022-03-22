/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:17:09 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/22 12:57:00 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	press_red_cross(t_data *data)
{
	ft_free(data);
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

	data->mlx = mlx;
	mlx->screen_heigth = 800;
	mlx->screen_width = 800;
}

/*
* W = 13, S = 1, D = 2, A = 0
*/
int		deal_key(int key_code, t_data *data)
{
	t_pos pos_p;

	pos_p = ft_get_pos_player(data->map);
	if (key_code == 53)
		exit(0);
	if (key_code == 13)
	{
		if (data->map[(int)(data->ray->posx + (data->ray->dirx * data->
					ray->movespeed * 2))][(int)data->ray->posy] != '1')
			data->ray->posx += data->ray->dirx * data->ray->movespeed;
		if (data->map[(int)(data->ray->posx)][(int)(data->ray->posy +
					(data->ray->diry * data->ray->movespeed * 2))] != '1')
			data->ray->posy += data->ray->diry * data->ray->movespeed;
		printf("W\n");
	}
	if (key_code == 1)
	{
		if (data->map[(int)(data->ray->posx - (data->ray->dirx * data->
						ray->movespeed * 2))][(int)(data->ray->posy)] != '1')
			data->ray->posx -= data->ray->dirx * data->ray->movespeed;
		if (data->map[(int)(data->ray->posx)][(int)(data->ray->posy -
					(data->ray->diry * data->ray->movespeed * 2))] != '1')
			data->ray->posy -= data->ray->diry * data->ray->movespeed;
		printf("S\n");
	}
	if (key_code == 2)
	{
		if (data->map[(int)(data->ray->posx + data->ray->diry *
					(data->ray->movespeed * 2))][(int)data->ray->posy] != '1')
			data->ray->posx += data->ray->diry * data->ray->movespeed;
		if (data->map[(int)data->ray->posx][(int)(data->ray->posy -
					data->ray->dirx *
					(data->ray->movespeed * 2))] != '1')
			data->ray->posy -= data->ray->dirx * data->ray->movespeed;
		printf("D\n");
	}
	if (key_code == 0)
	{
		if (data->map[(int)(data->ray->posx - data->ray->diry *
					(data->ray->movespeed * 2))][(int)data->ray->posy] != '1')
			data->ray->posx -= data->ray->diry * data->ray->movespeed;
		if (data->map[(int)data->ray->posx][(int)(data->ray->posy +
					data->ray->dirx *
					(data->ray->movespeed * 2))] != '1')
			data->ray->posy += data->ray->dirx * data->ray->movespeed;
		printf("A\n");
	}
	ft_ray(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_window, data->mlx->img.img_ptr, 0, 0);
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
	ray.posx = pos_player.x;
	ray.posy = pos_player.y;
	ray.planex = 0;
	ray.planey = 0.66;
	ray.movespeed = 1;
	ray.rotspeed = 1;
	data.ray = &ray;
	ft_ray(&data);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_window, mlx.img.img_ptr, 0, 0);
	mlx_hook(mlx.mlx_window, 17, 1L << 5, press_red_cross, &data);
	mlx_hook(mlx.mlx_window, 2, 0, deal_key, &data);
	mlx_loop(mlx.mlx);
	// ft_free_tab(data.map);
	// ft_free(&data);
	// system("leaks cub3d");
	return (0);
}
