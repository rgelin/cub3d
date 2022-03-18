/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 04:39:56 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/18 04:32:59 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_line_file(char *file_path)
{
	int	fd;
	int	nb_line;
	char *line;
	
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		ft_perror("Error: open file");
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

int	check_if_all_info(t_data *data)
{
	if (data->EA_texture_path && data->NO_texture_path && data->SO_texture_path
		&& data->WE_texture_path && data->floor_color && data->roof_color)
		return (1);
	else
		return (0);
}

void	parse_data(t_data *data, char **file_content)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (file_content && file_content[i] && !check_if_all_info(data))
	{
		if (ft_strlen(file_content[i]) == 0)
			i++;
		else
		{
			if (!data->NO_texture_path && !ft_strncmp(file_content[i], "NO ", 3))
				data->NO_texture_path = ft_strdup(file_content[i]);
			else if (!data->SO_texture_path && !ft_strncmp(file_content[i], "SO ", 3))
				data->SO_texture_path = ft_strdup(file_content[i]);
			else if (!data->WE_texture_path && !ft_strncmp(file_content[i], "WE ", 3))
				data->WE_texture_path = ft_strdup(file_content[i]);
			else if (!data->EA_texture_path && !ft_strncmp(file_content[i], "EA ", 3))
				data->EA_texture_path = ft_strdup(file_content[i]);
			else if (!data->floor_color && !ft_strncmp(file_content[i], "F ", 2))
				data->floor_color = ft_strdup(file_content[i]);
			else if (!data->roof_color && !ft_strncmp(file_content[i], "C ", 2))
				data->roof_color = ft_strdup(file_content[i]);
			else
				data->map[j++] = ft_strdup(file_content[i]);
			i++;
		}
	}
	while (file_content[i] && ft_strlen(file_content[i]) == 0)
		i++;
	while (file_content[i])
		data->map[j++] = ft_strdup(file_content[i++]);
	data->map[j] = NULL;
}

void	read_file(char *file_path, t_data *data)
{
	int fd;
	int	i;
	char	**file_content;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		ft_perror("Error: open file");
	file_content = malloc(sizeof(char *) * (count_line_file(file_path) + 1));
	data->map = malloc(sizeof(char *) * (count_line_file(file_path)));
	if (!file_content || !data->map)
		ft_perror("Error: malloc");
	i = 0;
	while (i < count_line_file(file_path))
	{
		line = get_next_line(fd);
		file_content[i] = ft_strdup(line);
		i++;
		free(line);
	}
	file_content[i] = NULL;
	parse_data(data, file_content);
	ft_free_tab(file_content);
	// i = -1;
	// while (data->map[++i])
	// 	printf("%s\n", data->map[i]);
	close(fd);
}

void	get_split_data(char **str)
{
	char **split;

	split = ft_split(*str, ' ');
	if (!split)
		ft_perror("Error: malloc");
	free(*str);
	*str = NULL;
	*str = ft_strdup(split[1]);
	ft_free_tab(split);
	
}

void split_data(t_data *data)
{
	get_split_data(&data->NO_texture_path);
	get_split_data(&data->SO_texture_path);
	get_split_data(&data->WE_texture_path);
	get_split_data(&data->EA_texture_path);
	get_split_data(&data->roof_color);
	get_split_data(&data->floor_color);
	check_color(data->roof_color);
	check_color(data->floor_color);
}
