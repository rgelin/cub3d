/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:30:35 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/14 12:57:51 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include "./minilibx/mlx.h"
#include "./libft/libft.h"

typedef struct s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef struct	s_data
{
	void	*mlx;
	void	*mlx_window;
	int		screen_width;
	int		screen_heigth;
	
	char	*file_path;
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
int		check_data(t_data *data);
void	check_color(char *color);

//============PARSING============//

int		count_line_file(char *file_path);
void	read_file(char *file_path, t_data *data);
void	get_split_data(char **str);
void	split_data(t_data *data);

//============PARSING============//

t_pos	ft_get_pos_player(char **map);