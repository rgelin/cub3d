/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:17:09 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/10 04:15:47 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_perror(char *msg, int return_value)
{
	printf("%s\n", msg);
	exit(return_value);
}

int	press_red_cross(t_mlx *mlx)
{
	(void)mlx;
	exit(EXIT_SUCCESS);
}

int	check_map_format(char *str)
{
	int 	i;
	int		j;
	char	*to_check;

	i = ft_strlen(str) - 1;
	j = 0;
	to_check = malloc(sizeof(char) * ft_strlen(str));
	if (!to_check)
		return (ft_perror("Error: malloc", 1));
	while (str[i] && str[i + 1] != '.')
		to_check[j++] = str[i--];
	to_check[j] = '\0';
	ft_rev_tab(to_check, 0);
	if (ft_strncmp(to_check, ".cub", 5))
	{
		free(to_check);
		return (ft_perror("Error: map format", 1));
	}
	free(to_check);
	return (0);
}

void	read_file(char *file_path, t_data *data)
{
	int fd;
	int	i;
	int	nb_line;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		ft_perror("Error: open file", 1);
	nb_line = 0;
	while (get_next_line(fd))
		nb_line++;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		ft_perror("Error: open file", 1);
	data->data = malloc(sizeof(char *) * (nb_line + 1));
	if (!data->data)
		ft_perror("Error: malloc", 1);
	i = -1;
	while (++i < nb_line)
		data->data[i] = get_next_line(fd);
	data->data[i] = NULL;
}

int	main(int ac, char *av[])
{
	(void)av;
	t_mlx mlx;
	t_data data;

	if (ac != 2)
		return (ft_perror("Error: argument", 1));
	check_map_format(av[1]);
	read_file(av[1], &data);
	mlx.mlx = mlx_init();
	// mlx.mlx_window = mlx_new_window(mlx.mlx, 800, 800, "cub3d");
	// mlx_hook(mlx.mlx_window, 17, 1L << 5, press_red_cross, &mlx);
	// mlx_loop(mlx.mlx);
	exit(EXIT_SUCCESS);
}