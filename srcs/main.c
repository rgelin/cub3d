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
<<<<<<< HEAD
	ft_free(mlx->data);
	// system("leaks cub3d");
	exit(EXIT_SUCCESS);
}


void init_struct(t_data *data, t_mlx *mlx)
=======
	(void)data;
	ft_free(data);
	exit(EXIT_SUCCESS);
}

void init_struct(t_data *data)
>>>>>>> d5527f3c97395014ffb28c6cfe7325696177d28c
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
<<<<<<< HEAD
	t_data	data;
	t_mlx	mlx;
=======
	t_data data;
	t_pos	pos_player;
>>>>>>> d5527f3c97395014ffb28c6cfe7325696177d28c

	if (ac != 2)
		return (ft_perror("Error: argument"));
	check_map_format(av[1]);
	init_struct(&data, &mlx);
	read_file(av[1], &data);
	if (check_data(&data))
		return (ft_perror("Error: operation file corrupted"));
	split_data(&data);
<<<<<<< HEAD
	mlx.mlx = mlx_init();
	mlx.mlx_window = mlx_new_window(mlx.mlx, mlx.screen_width, mlx.screen_heigth, "cub3d");
	mlx_hook(mlx.mlx_window, 17, 1L << 5, press_red_cross, &mlx);
	mlx_loop(mlx.mlx);
=======
	pos_player = ft_get_pos_player(data.map);
	data.mlx = mlx_init();
	data.mlx_window = mlx_new_window(data.mlx, 800, 600, "cub3d");
	data.img.img_ptr = mlx_new_image(data.mlx, 800, 600);
	data.img.data = (int *)mlx_get_data_addr(data.img.img_ptr, &data.img.bpp,
		&data.img.size_l, &data.img.endian);
	
	double	cameraX = 0;
	double	rayDirX = 0.0, rayDirY = 0.0, sideDistX = 0.0, sideDistY = 0.0;
	double	deltaDistX = 0.0, deltaDistY = 0.0, perpWallDist = 0.0, dirX = -1, dirY = 0;
	double	planeX = 0, planeY = 0.66;
	int		mapX = 0, mapY = 0, stepX = 0, stepY = 0, hit = 0, side = 0, hauteurLigne, drawStart = 0, drawEnd = 0;
	
		for(int x = 0; x < 600; x++)
		{
			cameraX = 2 * x / (double)600 - 1;
			rayDirX = dirX + planeX * cameraX;
			rayDirY = dirY + planeY * cameraX;
			mapX = pos_player.x;
			mapY = pos_player.y;
			deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
			deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
			if(rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (pos_player.x - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - pos_player.x) * deltaDistX;
			}
			if(rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (pos_player.y - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - pos_player.y) * deltaDistY;
			}
			while(hit == 0)
			{
				if(sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				if(data.map[mapX][mapY] == 1) 
					hit = 1;
			}
			if (side == 0)
				perpWallDist = sideDistX - deltaDistX;
			else
				perpWallDist = sideDistY - deltaDistY;
			hauteurLigne = (int)(600 / perpWallDist);
			drawStart = -hauteurLigne / 2 + 600 / 2;
			if(drawStart < 0) 
				drawStart = 0;
			drawEnd = hauteurLigne / 2 + 600 / 2;
			if(drawEnd >= 600)
				drawEnd = 600 - 1;
			int color = 0x960018;
			if(side == 1)
				color = color / 2;
			int y = drawStart;
			while (y < drawEnd)
			{
				data.img.data[x+ y] = color;
				// mlx_pixel_put(data.mlx, data.mlx_window, x, y, color);
				y++;
			}
			if (drawEnd < 0)
				drawEnd = 600;
			y=drawEnd;
			while (y < 600)
			{
				// data.img.data[y * 600 + x] = 0x464646;
				// data.img.data[(600 - y - 1) * 800 + x] = 0x007BA7;
				y++;
			}
		// printf("rayPosX = %f\n", rayPosX);
		// printf("rayPosY = %f\n", rayPosY);
		// printf("deltaDistX = %f\n", deltaDistX);
		// printf("deltaDistY = %f\n", deltaDistY);
		// printf("sideDistX = %f\n", sideDistX);
		// printf("sideDistY = %f\n", sideDistY);
		// printf("perpWallDist = %f\n", perpWallDist);
		// printf("Hauteur ligne = %d\n", hauteurLigne);
		}
	mlx_put_image_to_window(data.mlx, data.mlx_window, data.img.img_ptr, 0, 0);
	mlx_hook(data.mlx_window, 17, 1L << 5, press_red_cross, &data.mlx);
	mlx_hook(data.mlx_window, 2, 0, &deal_key, &data);
	mlx_loop(data.mlx);
>>>>>>> d5527f3c97395014ffb28c6cfe7325696177d28c
	// ft_free_tab(data.map);
	// ft_free(&data);
	// system("leaks cub3d");
	return (0);
}
