/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 03:05:56 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/11 21:28:47 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_perror(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	ft_free(t_data *data)
{
	if (data)
	{
		free(data->NO_texture_path);
		free(data->SO_texture_path);
		free(data->WE_texture_path);
		free(data->EA_texture_path);
		free(data->roof_color);
		free(data->floor_color);
		ft_free_tab(data->map);
	}
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

