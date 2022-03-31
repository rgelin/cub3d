/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:56:00 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/31 15:59:46 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_surounded(t_data *data)
{
	int		i;
	int		j;

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
				if (j != (int)ft_strlen(data->map[i] - 1)
					&& data->map[i][j + 1] == ' ')
					return (1);
				if (i != 0 && data->map[i - 1][j] == ' ')
					return (1);
				if (i != ft_tabsize(data->map) - 1
					&& data->map[i + 1][j] == ' ')
					return (1);
			}
		}
	}
	return (0);
}

static int	check_up_and_down(t_data *data)
{
	int	j;

	if (!data->no_texture_path || !data->so_texture_path
		|| !data->we_texture_path || ! data->ea_texture_path
		|| !data->floor_color || !data->roof_color)
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

static int	check_empty_line(t_data *data, int i)
{
	char	*trim;

	if (data->map[i])
		trim = ft_strtrim(data->map[i], " ");
	if (data->map[i] && ft_strlen(trim) == 0)
	{
		free(trim);
		return (1);
	}
	free(trim);
	return (0);
}

int	check_contains_valid_char(t_data *data, int i, int j)
{
	char	*trim;

	trim = ft_strtrim(data->map[i], " ");
	if (trim[0] != '1' || trim[ft_strlen(trim) - 1] != '1')
	{
		free(trim);
		return (1);
	}
	free(trim);
	trim = NULL;
	if (data->map[i][j] != ' ' && data->map[i][j] != '0'
		&& data->map[i][j] != '1' && data->map[i][j] != 'N'
		&& data->map[i][j] != 'S' && data->map[i][j] != 'W'
		&& data->map[i][j] != 'E')
		return (1);
	return (0);
}

int	check_data(t_data *data)
{
	int		i;
	int		j;
	int		pos;

	i = -1;
	pos = 0;
	if (ft_tabsize(data->map) == 0 || check_up_and_down(data))
		return (1);
	while (data->map && data->map[++i])
	{
		j = -1;
		if (check_empty_line(data, i))
			return (1);
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
				pos++;
			if (check_contains_valid_char(data, i, j))
				return (1);
		}
	}
	if (pos != 1 || check_surounded(data))
		return (1);
	return (0);
}
