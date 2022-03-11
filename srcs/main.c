/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:17:09 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/11 21:30:22 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	press_red_cross(t_data *data)
{
	ft_free(data);
	exit(EXIT_SUCCESS);
}

int		count_line_file(char *file_path)
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
	i = -1;
	j = -1;
	while (++i < count_line_file(file_path) + 1)
	{
		line = get_next_line(fd);
		if (ft_strlen(line) == 0)
			i++;
		else if (!ft_strncmp(line, "NO ", 3))
			data->NO_texture_path = ft_strdup(line);
		else if (!ft_strncmp(line, "SO ", 3))
			data->SO_texture_path = ft_strdup(line); //leak ???? Pq ? Aucun sens
		else if (!ft_strncmp(line, "WE ", 3))
			data->WE_texture_path = ft_strdup(line);
		else if (!ft_strncmp(line, "EA ", 3))
			data->EA_texture_path = ft_strdup(line);
		else if (!ft_strncmp(line, "F ", 2))
			data->floor_color = ft_strdup(line);
		else if (!ft_strncmp(line, "C ", 2))
			data->roof_color = ft_strdup(line);
		else
			data->map[++j] = ft_strdup(line);
		free(line);
		
	}
	data->map[++j] = NULL;
	i = -1;
	while (data->map && data->map[++i])
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
	// ft_free_tab(split);
	printf("%s\n", data->NO_texture_path);
	printf("%s\n", data->SO_texture_path);
	printf("%s\n", data->WE_texture_path);
	printf("%s\n", data->EA_texture_path);
	printf("%s\n", data->roof_color);
	printf("%s\n", data->floor_color);
}

int	check_data(t_data *data)
{
	int	i;
	int	j;
	
	if (!data->NO_texture_path || !data->SO_texture_path || !data->WE_texture_path
		|| ! data->EA_texture_path || !data->floor_color || !data->roof_color)
		return (1);
	i = -1;
	while (data && data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] != ' ' && data->map[i][j] != '0' && data->map[i][j] != '1' && data->map[i][j] != 'N'
				&& data->map[i][j] != 'S' && data->map[i][j] != 'W' && data->map[i][j] != 'E')
				return (1);			
		}
	}
	return (0);
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

int	main(int ac, char *av[])
{
	t_data data;

	if (ac != 2)
		return (ft_perror("Error: argument"));
	data.file_path = av[1];
	check_map_format(av[1]);
	init_struct(&data);
	read_file(av[1], &data);
	if (check_data(&data))
		return (ft_perror("Error: operation file corrupted"));
	split_data(&data);
	// data.mlx = mlx_init();
	// mlx.mlx_window = mlx_new_window(mlx.mlx, 800, 800, "cub3d");
	// mlx_hook(mlx.mlx_window, 17, 1L << 5, press_red_cross, &mlx);
	// mlx_loop(mlx.mlx);
	// ft_free_tab(data.map);
	// ft_free(&data);
	system("leaks cub3d");
	return (0);
}