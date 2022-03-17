/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:17:09 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/17 12:57:11 by jvander-         ###   ########.fr       */
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
	for (int x = 0; x < mlx.screen_width; x++)
	{
		ray.camerax = 1.5 * x / mlx.screen_width - 1;
		ray.raydirx = ray.dirx + ray.planex * ray.camerax;
		ray.raydiry = ray.diry + ray.planey * ray.camerax;
		ray.mapx = pos_player.x;
		ray.mapy = pos_player.y;
		ray.deltadistx = fabs(1 / ray.raydirx);
		ray.deltadisty = fabs(1 / ray.raydiry);
		ray.hit = 0;
		if (ray.raydirx < 0)
		{
			ray.stepx = -1;
			ray.sidedistx = (pos_player.x - ray.mapx) * ray.deltadistx;
		}
		else
		{
			ray.stepx = 1;
			ray.sidedistx = (ray.mapx + 1.0 - pos_player.x) * ray.deltadistx;
		}
		if (ray.raydiry < 0)
		{
			ray.stepy = -1;
			ray.sidedisty = (pos_player.y - ray.mapy) * ray.deltadisty;
		}
		else
		{
			ray.stepy = 1;
			ray.sidedisty = (ray.mapy + 1.0 - pos_player.y) * ray.deltadisty;
		}
		while (ray.hit == 0)
		{
			if (ray.sidedistx < ray.sidedisty)
			{
				ray.sidedistx += ray.deltadistx;
				ray.mapx += ray.stepx;
				ray.side = 0;
			}
			else
			{
				ray.sidedisty += ray.deltadisty;
				ray.mapy += ray.stepy;
				ray.side = 1;
			}
			if (data.map[ray.mapx][ray.mapy] == '1')
				ray.hit = 1;
		}
		if (ray.side == 0)
			ray.perpwalldist = (ray.sidedistx - ray.deltadistx);
		else
			ray.perpwalldist = (ray.sidedisty - ray.deltadisty);
		ray.lineheight = mlx.screen_heigth / ray.perpwalldist;
		ray.drawstart = -ray.lineheight / 2 + mlx.screen_heigth / 2;
		if (ray.drawstart < 0)
			ray.drawstart = 0;
		ray.drawend = ray.lineheight / 2 + mlx.screen_heigth / 2;
		if (ray.drawend >= mlx.screen_heigth)
			ray.drawend = mlx.screen_heigth - 1;
		int y = ray.drawstart;
		while (y < ray.drawend)
		{
			int color = 0xf2f2f2;;
			if (ray.side == 1)
				color /= 0xCCCCCC;
			mlx.img.data[y * mlx.img.size_l / 4 + x] = color;
			y++;
		}
		if (ray.drawend < 0)
			ray.drawend = mlx.screen_heigth;
 		y = ray.drawend;
		while (y < mlx.screen_heigth)
		{
 			mlx.img.data[y * mlx.img.size_l / 4 + x] = 0xCC6600;
			// x,h-y-1,0xcc0000
			// mlx.img.data[y * (mlx.screen_heigth - 1) / 4 + x] = 0x00FFFF;
			y++;
		}
		y = ray.drawstart;
		while (y >= 0)
		{
			mlx.img.data[y * mlx.img.size_l / 4 + x] = 0x00FFFF;
			y--;
		}
	}
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_window, mlx.img.img_ptr, 0, 0);
	mlx_hook(mlx.mlx_window, 17, 1L << 5, press_red_cross, &mlx);
	mlx_hook(mlx.mlx_window, 2, 0, deal_key, &mlx);
	mlx_loop(mlx.mlx);
	// ft_free_tab(data.map);
	// ft_free(&data);
	// system("leaks cub3d");
	return (0);
}
