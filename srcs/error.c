/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 03:05:56 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/18 04:40:29 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_perror(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	// system("leaks cub3d");
	exit(EXIT_FAILURE);
}

void	ft_free(t_data *data)
{
	free(data->NO_texture_path);
	free(data->SO_texture_path);
	free(data->WE_texture_path);
	free(data->EA_texture_path);
	free(data->roof_color);
	free(data->floor_color);
	ft_free_tab(data->map);
}

void	check_map_format(char *str)
{
	int 	i;
	int		j;
	char	*to_check;

	i = ft_strlen(str) - 1;
	j = 0;
	to_check = malloc(sizeof(char) * ft_strlen(str));
	if (!to_check)
		ft_perror("Error: malloc");
	while (str[i] && str[i + 1] != '.')
		to_check[j++] = str[i--];
	to_check[j] = '\0';
	ft_rev_tab(to_check, 0);
	if (ft_strncmp(to_check, ".cub", 5))
		ft_perror("Error: map format");
	free(to_check);
}

void	check_color(char *color)
{
	char	**split_color;
	int		i;
	int		j;

	split_color = ft_split(color, ',');
	if (!split_color)
		ft_perror("Error: malloc");
	if (ft_tabsize(split_color) != 3)
		ft_perror("Error: operation file corrupted");
	i = -1;
	while (split_color[++i])
	{
		j = -1;
		while (split_color[i][++j])
		{
			if (!ft_isdigit(split_color[i][j]))
				ft_perror("Error: operation file corrupted");
		}
		if (ft_atoi(split_color[i]) < 0 || ft_atoi(split_color[i]) > 255)
			ft_perror("Error: operation file corrupted");
	}
	ft_free_tab(split_color);
}

int	check_data(t_data *data)
{
	int	i;
	int	j;
	
	if (!data->NO_texture_path || !data->SO_texture_path || !data->WE_texture_path
		|| ! data->EA_texture_path || !data->floor_color || !data->roof_color)
		return (1);
	i = -1;
	j = -1;
	while (data->map[ft_tabsize(data->map) - 1][++j])
	{
			if ((data->map[0][j] != '1' && data->map[0][j] != ' '))
				return (1);		
			if (data->map[ft_tabsize(data->map) - 1][j] != '1'
				&& data->map[ft_tabsize(data->map) - 1][j] != ' ')
				return (1);		
	}
	while (data->map && data->map[++i])
	{
		j = -1;
		if (data->map[i] && ft_strlen(data->map[i]) == 0)
			return (1);
		while (data->map[i][++j])
		{
			if (data->map[i][j] != ' ' && data->map[i][j] != '0' && data->map[i][j] != '1' && data->map[i][j] != 'N'
				&& data->map[i][j] != 'S' && data->map[i][j] != 'W' && data->map[i][j] != 'E')
				return (1);
			// if (data->map[i + 1] && (data->map[i][j] == ' ' || data->map[i][j] == '0' && (data->map[i + 1][j] != ' ' && data->map[i + 1][j] != '1')))
			// 	return (1);
		}
	}
	return (0);
}
