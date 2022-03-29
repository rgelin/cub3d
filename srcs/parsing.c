/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 04:39:56 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/29 15:36:40 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_line_file(char *file_path, t_data *data)
{
	int		fd;
	int		nb_line;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		ft_perror("Error: open file", data);
	nb_line = 0;
	line = get_next_line(fd);
	if (line)
		nb_line++;
	while (line)
	{
		nb_line++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (nb_line);
}

static void	dispatch_data(t_data *data, char **file_content, int i, int *j)
{
	if (!data->no_texture_path && !ft_strncmp(file_content[i], "NO ", 3))
		data->no_texture_path = ft_strdup(file_content[i]);
	else if (!data->so_texture_path && !ft_strncmp(file_content[i], "SO ", 3))
		data->so_texture_path = ft_strdup(file_content[i]);
	else if (!data->we_texture_path && !ft_strncmp(file_content[i], "WE ", 3))
		data->we_texture_path = ft_strdup(file_content[i]);
	else if (!data->ea_texture_path && !ft_strncmp(file_content[i], "EA ", 3))
		data->ea_texture_path = ft_strdup(file_content[i]);
	else if (!data->floor_color && !ft_strncmp(file_content[i], "F ", 2))
		data->floor_color = ft_strdup(file_content[i]);
	else if (!data->roof_color && !ft_strncmp(file_content[i], "C ", 2))
		data->roof_color = ft_strdup(file_content[i]);
	else
		data->map[(*j)++] = ft_strdup(file_content[i]);
}

void	parse_data(t_data *data, char **file_content)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (file_content && file_content[i] && !check_if_all_info(data))
	{
		if (ft_strlen(file_content[i]) == 0)
			i++;
		else
		{
			dispatch_data(data, file_content, i, &j);
			i++;
		}
	}
	while (file_content[i] && ft_strlen(file_content[i]) == 0)
		i++;
	while (file_content[i])
	{
		data->map[j] = ft_strdup(file_content[i++]);
		if (!data->map[j++])
			ft_perror("Error: malloc", data);
	}
	data->map[j] = NULL;
}

void	get_split_data(char **str, t_data *data)
{
	char	**split;

	split = ft_split(*str, ' ');
	if (!split)
		ft_perror("Error: malloc", data);
	free(*str);
	*str = NULL;
	*str = ft_strdup(split[1]);
	ft_free_tab(split);
}

void	split_data(t_data *data)
{
	get_split_data(&data->no_texture_path, data);
	get_split_data(&data->so_texture_path, data);
	get_split_data(&data->we_texture_path, data);
	get_split_data(&data->ea_texture_path, data);
	get_split_data(&data->roof_color, data);
	get_split_data(&data->floor_color, data);
	check_color(data->roof_color, data);
	check_color(data->floor_color, data);
	data->hex_floor_color = convert_color(data->floor_color);
	data->hex_roof_color = convert_color(data->roof_color);
}
