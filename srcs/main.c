/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:17:09 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/30 16:08:33 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	press_red_cross(t_data *data)
{
	ft_free(data);
	exit(EXIT_SUCCESS);
}

int	deal_key(int key_code, t_data *data)
{
	t_pos	pos_p;

	pos_p = ft_get_pos_player(data->map);
	if (key_code == 53)
	{
		ft_free(data);
		exit(EXIT_SUCCESS);
	}
	if (key_code == 13)
		ft_move_up(data);
	if (key_code == 1)
		ft_move_down(data);
	if (key_code == 2)
		ft_move_right(data);
	if (key_code == 0)
		ft_move_left(data);
	if (key_code == 123)
		ft_rotate_left(data);
	if (key_code == 124)
		ft_rotate_right(data);
	return (0);
}

void	read_file(char *file_path, t_data *data)
{
	int		fd;
	int		i;
	char	**file_content;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		ft_perror("Error: open file", data);
	file_content = malloc(sizeof(char *)
			* (count_line_file(file_path, data) + 1));
	data->map = malloc(sizeof(char *) * (count_line_file(file_path, data)));
	if (!file_content || !data->map)
		ft_perror("Error: malloc", data);
	i = 0;
	while (i < count_line_file(file_path, data))
	{
		line = get_next_line(fd);
		file_content[i] = ft_strdup(line);
		i++;
		free(line);
	}
	file_content[i] = NULL;
	parse_data(data, file_content);
	ft_free_tab(file_content);
	close(fd);
}

int	main(int ac, char *av[])
{
	t_mlx	mlx;
	t_data	data;
	t_ray	ray;

	init_struct(&data, &mlx);
	if (ac != 2)
		ft_perror("Error: argument", &data);
	check_map_format(av[1], &data);
	ft_parse_and_init(&data, &mlx, &ray, av[1]);
	mlx_hook(mlx.mlx_window, 17, 1L << 5, press_red_cross, &data);
	mlx_hook(mlx.mlx_window, 2, 0, deal_key, &data);
	mlx_loop_hook(mlx.mlx, ft_ray, &data);
	mlx_loop(mlx.mlx);
	return (0);
}
