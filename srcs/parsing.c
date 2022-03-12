/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 04:39:56 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/12 05:13:47 by rgelin           ###   ########.fr       */
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

void	dispatch_data(t_data **data, char *line, int j)
{
	
	// printf("%s\n", line);
	// printf("%d\n", j);
	if (!(*data)->NO_texture_path && !ft_strncmp(line, "NO ", 3))
		(*data)->NO_texture_path = ft_strdup(line);
	else if (!(*data)->SO_texture_path && !ft_strncmp(line, "SO ", 3))
		(*data)->SO_texture_path = ft_strdup(line);
	else if (!(*data)->WE_texture_path && !ft_strncmp(line, "WE ", 3))
		(*data)->WE_texture_path = ft_strdup(line);
	else if (!(*data)->EA_texture_path && !ft_strncmp(line, "EA ", 3))
		(*data)->EA_texture_path = ft_strdup(line);
	else if (!(*data)->floor_color && !ft_strncmp(line, "F ", 2))
		(*data)->floor_color = ft_strdup(line);
	else if (!(*data)->roof_color && !ft_strncmp(line, "C ", 2))
		(*data)->roof_color = ft_strdup(line);
	else
		(*data)->map[j] = ft_strdup(line);
	// printf("%s\n", data->map[j]);
}

void	read_file(char *file_path, t_data *data)
{
	int fd;
	int	i;
	int	j;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		ft_perror("Error: open file");
	data->map = malloc(sizeof(char *) * (count_line_file(file_path)));
	if (!data->map)
		ft_perror("Error: malloc");
	i = 0;
	j = -1;
	while (i < count_line_file(file_path) + 1)
	{
		line = get_next_line(fd);
		if (ft_strlen(line) == 0)
			i++;
		else
		{
			// dispatch_data(&data, line, j);
			// i++;
			// j++;
			if (!data->NO_texture_path && !ft_strncmp(line, "NO ", 3))
				data->NO_texture_path = ft_strdup(line);
			else if (!data->SO_texture_path && !ft_strncmp(line, "SO ", 3))
				data->SO_texture_path = ft_strdup(line);
			else if (!data->WE_texture_path && !ft_strncmp(line, "WE ", 3))
				data->WE_texture_path = ft_strdup(line);
			else if (!data->EA_texture_path && !ft_strncmp(line, "EA ", 3))
				data->EA_texture_path = ft_strdup(line);
			else if (!data->floor_color && !ft_strncmp(line, "F ", 2))
				data->floor_color = ft_strdup(line);
			else if (!data->roof_color && !ft_strncmp(line, "C ", 2))
				data->roof_color = ft_strdup(line);
			else
				data->map[++j] = ft_strdup(line);
			i++;
		}
	
		free(line);
		
	}
	data->map[++j] = NULL;
	// printf("%s\n", data->NO_texture_path);
	i = -1;
	while (data->map[++i])
		printf("%s\n", data->map[i]);
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
