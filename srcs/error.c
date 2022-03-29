/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 03:05:56 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/29 15:36:40 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_if_all_info(t_data *data)
{
	if (data->ea_texture_path && data->no_texture_path && data->so_texture_path
		&& data->we_texture_path && data->floor_color && data->roof_color)
		return (1);
	else
		return (0);
}

void	ft_free(t_data *data)
{
	int	i;

	if (data->no_texture_path)
		free(data->no_texture_path);
	if (data->so_texture_path)
		free(data->so_texture_path);
	if (data->we_texture_path)
		free(data->we_texture_path);
	if (data->ea_texture_path)
		free(data->ea_texture_path);
	if (data->roof_color)
		free(data->roof_color);
	if (data->floor_color)
		free(data->floor_color);
	ft_free_tab(data->map);
	if (data->mlx)
		mlx_destroy_image(data->mlx->mlx, data->mlx->img.img_ptr);
	i = -1;
	while (++i < 4)
	{
		if (data->mlx->mlx && data->texture[i].img_ptr)
			mlx_destroy_image(data->mlx->mlx, data->texture[i].img_ptr);
	}
	mlx_destroy_window(data->mlx->mlx, data->mlx->mlx_window);
}

int	ft_perror(char *msg, t_data *data)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	ft_free(data);
	exit(EXIT_FAILURE);
}

void	check_map_format(char *str, t_data *data)
{
	int		i;
	int		j;
	char	*to_check;

	i = ft_strlen(str) - 1;
	j = 0;
	to_check = malloc(sizeof(char) * ft_strlen(str));
	if (!to_check)
		ft_perror("Error: malloc", data);
	while (str[i] && str[i + 1] != '.')
		to_check[j++] = str[i--];
	to_check[j] = '\0';
	ft_rev_tab(to_check, 0);
	if (ft_strncmp(to_check, ".cub", 5))
		ft_perror("Error: map format", data);
	free(to_check);
}

void	check_color(char *color, t_data *data)
{
	char	**split_color;
	int		i;
	int		j;

	split_color = ft_split(color, ',');
	if (!split_color)
		ft_perror("Error: malloc", data);
	if (ft_tabsize(split_color) != 3)
		ft_perror("Error: operation file corrupted", data);
	i = -1;
	while (split_color[++i])
	{
		j = -1;
		while (split_color[i][++j])
		{
			if (!ft_isdigit(split_color[i][j]))
				ft_perror("Error: operation file corrupted", data);
		}
		if (ft_atoi(split_color[i]) < 0 || ft_atoi(split_color[i]) > 255)
			ft_perror("Error: operation file corrupted", data);
	}
	ft_free_tab(split_color);
}
