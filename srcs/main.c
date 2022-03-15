/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:17:09 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/15 16:41:10 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	press_red_cross(t_data *data)
{
	(void)data;
	ft_free(data);
	exit(EXIT_SUCCESS);
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
	data.mlx_window = mlx_new_window(data.mlx, 800, 600, "cub3d");
	data.img.img_ptr = mlx_new_image(data.mlx, 800, 600);
	data.img.data = (int *)mlx_get_data_addr(data.img.img_ptr, &data.img.bpp,
		&data.img.size_l, &data.img.endian);
	
	int		x = 0;
	double	cameraX = 0;
	double	rayPosX = 0.0, rayPosY = 0.0, rayDirX = 0.0, rayDirY = 0.0, sideDistX = 0.0, sideDistY = 0.0;
	double	deltaDistX = 0.0, deltaDistY = 0.0, perpWallDist = 0.0;
	int		mapX = 0, mapY = 0, stepX = 0, stepY = 0, hit = 0, side = 0, drawStart = 0, drawEnd = 0;
	double hauteurLigne;
	
	while (x <= 600)
	{
		cameraX = (2 * x / 600) - 1;
		rayPosX = pos_player.x;
		rayPosY = pos_player.y;
		mapX = (int)rayPosX;
		mapY = (int)rayPosY;
		if (rayDirX == 0)
			deltaDistX = 1e30;
		else
			deltaDistX = sqrtf(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		if (rayDirY == 0)
			deltaDistY = 1e30;
		else
			deltaDistY = sqrtf(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		printf("rayPosX = %f\n", rayPosX);
		printf("rayPosY = %f\n", rayPosY);
		printf("deltaDistX = %f\n", deltaDistX);
		printf("deltaDistY = %f\n", deltaDistY);
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (rayPosX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
		}
		printf("sideDistX = %f\n", sideDistX);
		printf("sideDistY = %f\n", sideDistY);
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
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
			// printf("x = %d | y = %d | content == %c\n", mapX, mapY, data.map[mapX][mapY]);
			if (data.map[mapX][mapY] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
		else
			perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);
		hauteurLigne = fabs(64 / perpWallDist);
		drawStart = -hauteurLigne / 2 + 64 / 2;
		drawEnd = hauteurLigne / 2 + 64 / 2;
		if (drawStart < 0)
			drawStart = 0;
		if (drawEnd >= 64)
			drawEnd = 64 - 1;
		int y = drawStart;
		while (y < drawEnd)
		{
			int color = 0xf2f2f2;
			if (side == 1)
				color = 0xCCCCCC;
			//Draw the line
			y++;
		}
		if (drawEnd < 0)
			drawEnd = 64;
		y = drawEnd;
		// while (y < 64)
		// {
		// 	Draw Ceilling
		// 	draw floor
		// 	y++;
		// }
		x++;
	}
	mlx_put_image_to_window(data.mlx, data.mlx_window, data.img.img_ptr, 0, 0);
	mlx_hook(data.mlx_window, 17, 1L << 5, press_red_cross, &data.mlx);
	mlx_hook(data.mlx_window, 2, 0, &deal_key, &data);
	mlx_loop(data.mlx);
	// ft_free_tab(data.map);
	// ft_free(&data);
	// system("leaks cub3d");
	return (0);
}
