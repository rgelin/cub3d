/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:17:09 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/11 00:04:36 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	press_red_cross(t_data *data)
{
	ft_free(data);
	exit(EXIT_SUCCESS);
}

void	read_file(char *file_path, t_data *data)
{
	int fd1;
	int	fd2;
	int	i;
	int	nb_line;

	fd1 = open(file_path, O_RDONLY);
	fd2 = open(file_path, O_RDONLY);
	if (fd1 == -1 || fd2 == -1)
		ft_perror("Error: open file");
	nb_line = 0;
	while (get_next_line(fd1))
		nb_line++;
	data->map = malloc(sizeof(char *) * (nb_line));
	data->data = malloc(sizeof(char *) * (nb_line + 1));
	if (!data->data || !data->map)
		ft_perror("Error: malloc");
	i = -1;
	while (++i < nb_line)
		data->data[i] = get_next_line(fd2);
	data->data[++i] = NULL;
	close(fd1);
	close(fd2);
}

void split_data(t_data *data)
{
	char **split;

	split = ft_split(data->NO_texture_path, ' ');
	data->NO_texture_path = split[1];
	free(split[0]);
	// ft_free_tab(split);
	split = ft_split(data->SO_texture_path, ' ');
	data->SO_texture_path = split[1];
	free(split[0]);
	// ft_free_tab(split);
	split = ft_split(data->WE_texture_path, ' ');
	data->WE_texture_path = split[1];
	free(split[0]);
	// ft_free_tab(split);
	split = ft_split(data->EA_texture_path, ' ');
	data->EA_texture_path = split[1];
	free(split[0]);
	// ft_free_tab(split);
	printf("%s\n", data->NO_texture_path);
	printf("%s\n", data->SO_texture_path);
	printf("%s\n", data->WE_texture_path);
	printf("%s\n", data->EA_texture_path);
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
	i = -1;
	while (data && data->map[++i])
		printf("%s\n", data->map[i]);
	return (0);
}

void	ft_parse_data(t_data *data)
{
	int i;
	int	j;

	i = 0;
	j = -1;
	while (data->data[i])
	{
		if (ft_strlen(data->data[i]) == 0)
			i++;
		else if (!ft_strncmp(data->data[i], "NO ", 3))
			data->NO_texture_path = data->data[i++];
		else if (!ft_strncmp(data->data[i], "SO ", 3))
			data->SO_texture_path = data->data[i++];
		else if (!ft_strncmp(data->data[i], "WE ", 3))
			data->WE_texture_path = data->data[i++];
		else if (!ft_strncmp(data->data[i], "EA ", 3))
			data->EA_texture_path = data->data[i++];
		else if (!ft_strncmp(data->data[i], "F ", 2))
			data->floor_color = data->data[i++];
		else if (!ft_strncmp(data->data[i], "C ", 2))
			data->roof_color = data->data[i++];
		else
			data->map[++j] = data->data[i++];
	}
	data->map[++j] = NULL;
}

int	main(int ac, char *av[])
{
	(void)av;
	t_data data;

	if (ac != 2)
		return (ft_perror("Error: argument"));
	check_map_format(av[1]);
	read_file(av[1], &data);
	ft_parse_data(&data);
	if (check_data(&data))
		return (ft_perror("Error: operation file corrupted"));
	data.mlx = mlx_init();
	// mlx.mlx_window = mlx_new_window(mlx.mlx, 800, 800, "cub3d");
	// mlx_hook(mlx.mlx_window, 17, 1L << 5, press_red_cross, &mlx);
	// mlx_loop(mlx.mlx);
	// system("leaks cub3d");
	exit(EXIT_SUCCESS);
}