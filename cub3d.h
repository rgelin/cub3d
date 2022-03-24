/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:30:35 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/24 16:02:22 by jvander-         ###   ########.fr       */
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
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

typedef struct s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_window;
	int		screen_width;
	int		screen_heigth;
	t_img	img;
}	t_mlx;

typedef struct s_tex
{
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		tex_num;
}				t_tex;

typedef struct s_ray
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
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
	double		movespeed;
	double		rotspeed;
}					t_ray;

typedef struct s_data
{
	char	**map;
	char	*NO_texture_path;
	char	*SO_texture_path;
	char	*WE_texture_path;
	char	*EA_texture_path;
	char	*floor_color;
	char	*roof_color;
	int		hex_floor_color;
	int		hex_roof_color;
	t_img	texture[4];
	t_mlx	*mlx;
	t_ray	*ray;
}	t_data;

//============ERRORS============//

int		ft_perror(char *msg);
void	ft_free(t_data *data);
void	check_map_format(char *str);
int		check_data(t_data *data);
void	check_color(char *color);
int		check_map(t_data *data);

//============PARSING============//

int		count_line_file(char *file_path);
void	read_file(char *file_path, t_data *data);
void	get_split_data(char **str);
void	split_data(t_data *data);

//============UTILS============//
t_pos	ft_get_pos_player(char **map);
int		ft_ray(t_data *data);
void	ft_draw_wall(t_ray *ray, t_mlx *mlx, int x, t_data *data);
void	ft_draw_floor_roof(t_ray *ray, t_mlx *mlx, int x, t_data *data);
long	convert_color(char *color_number);

//============MOVEMENTS============//
void	ft_move_down(t_data *data);
void	ft_move_right(t_data *data);
void	ft_move_left(t_data *data);
void	ft_move_up(t_data *data);
void	ft_rotate_left(t_data *data);
void	ft_rotate_right(t_data *data);

//============INIT============//
void	ft_parse_and_init(t_data *data, t_mlx *mlx, t_ray *ray, char *file);
void	ft_determine_start_orientation(t_data *data, t_ray *ray);
#endif