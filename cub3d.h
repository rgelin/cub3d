/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:30:35 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/17 11:39:23 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "./minilibx/mlx.h"
# include "./libft/libft.h"

typedef struct s_data
{
	char	**map;
	char	*NO_texture_path;
	char	*SO_texture_path;
	char	*WE_texture_path;
	char	*EA_texture_path;
	char	*floor_color;
	char	*roof_color;
}	t_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_window;
	int		screen_width;
	int		screen_heigth;
	t_data	*data;
}	t_mlx;

typedef struct s_ray
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planx;
	double		plany;
	double		raydirx;
	double		raydiry;
	double		camerax;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	double		perpwalldist;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			x;
}					t_ray;

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

#endif