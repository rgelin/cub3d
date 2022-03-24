/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:56:00 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/24 16:26:32 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_surounded(t_data *data)
{
	int i;
	int	j;

	i = -1;
	while (data->map && data->map[++i])
	{
		j = -1;
		while (data->map[i] && data->map[i][++j])
		{
			if (data->map[i][j] == '0')
			{
				if (j != 0 && data->map[i][j - 1] == ' ')
					return (1);
				if (j != (int)ft_strlen(data->map[i] - 1) && data->map[i][j + 1] == ' ')
					return (1);
				if (i != 0 &&  data->map[i - 1][j] == ' ')
					return (1);
				if (i != ft_tabsize(data->map) - 1 && data->map[i + 1][j] == ' ')
					return (1);
			}
		}
	}
	return (0);
}

int	check_up_and_down(t_data *data)
{
	int j;
	
	if (!data->NO_texture_path || !data->SO_texture_path || !data->WE_texture_path
		|| ! data->EA_texture_path || !data->floor_color || !data->roof_color)
		return (1);
	j = -1;
	while (data->map && data->map[ft_tabsize(data->map) - 1][++j])
	{
			if ((data->map[0][j] != '1' && data->map[0][j] != ' '))
				return (1);		
			if (data->map[ft_tabsize(data->map) - 1][j] != '1'
				&& data->map[ft_tabsize(data->map) - 1][j] != ' ')
				return (1);		
	}
	return (0);
}

int	check_data(t_data *data)
{
	int	i;
	int	j;
	int	pos;
	char *trim;
	
	i = -1;
	pos = 0;
	if (check_up_and_down(data))
		return (1);
	while (data->map && data->map[++i])
	{
		j = -1;
		if (data->map[i])
			trim = ft_strtrim(data->map[i], " ");
		if (data->map[i] && ft_strlen(trim) == 0)
		{
			free(trim);
			return (1);
		}
		free(trim);
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
				pos++;
			if (data->map[i][j] != ' ' && data->map[i][j] != '0' && data->map[i][j] != '1' && data->map[i][j] != 'N'
				&& data->map[i][j] != 'S' && data->map[i][j] != 'W' && data->map[i][j] != 'E')
				return (1);
		}
	}
	if (pos != 1 || check_surounded(data))
		return (1);
	return (0);
}
