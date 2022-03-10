/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:30:35 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/10 19:02:15 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include "./minilibx/mlx.h"
#include "./libft/libft.h"

typedef struct	s_data
{
	void	*mlx;
	void	*mlx_window;
	int		screen_width;
	int		screen_heigth;
	char	**data;
	char	**map;
	char	*NO_texture_path;
	char	*SO_texture_path;
	char	*WE_texture_path;
	char	*EA_texture_path;
	char	*floor_color;
	char	*roof_color;
}	t_data;

//============ERRORS============//

int		ft_perror(char *msg);
void	ft_free(t_data *data);
void	check_map_format(char *str);

