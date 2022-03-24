/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movments2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:01:25 by jvander-          #+#    #+#             */
/*   Updated: 2022/03/24 13:05:02 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	ft_get_orientation(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'O' || map[i][j] == 'E')
				return (map[i][j]);
		}
	}
	return (0);
}

static void	ft_set_or(t_ray *ray, double dirx, double diry, double p_x)
{
	ray->dirx = dirx;
	ray->diry = diry;
	ray->planex = p_x;
}

void	ft_determine_start_orientation(t_data *data, t_ray *ray)
{
	char	orientation;

	orientation = ft_get_orientation(data->map);
	if (orientation == 'N')
	{
		ft_set_or(ray, -1, 0, 0);
		ray->planey = 0.66;
	}
	else if (orientation == 'S')
	{
		ft_set_or(ray, 1, 0, 0);
		ray->planey = -0.66;
	}
	else if (orientation == 'E')
	{
		ft_set_or(ray, 0, 1, 0.66);
		ray->planey = 0;
	}
	else
	{
		ft_set_or(ray, 0, -1, -0.66);
		ray->planey = 0;
	}
}

void	ft_rotate_left(t_data *data)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->ray->dirx;
	oldplanex = data->ray->planex;
	data->ray->dirx = data->ray->dirx * cos(data->ray->rotspeed / 2)
		- data->ray->diry * sin(data->ray->rotspeed / 2);
	data->ray->diry = olddirx * sin(data->ray->rotspeed / 2)
		+ data->ray->diry * cos(data->ray->rotspeed / 2);
	data->ray->planex = data->ray->planex * cos(data->ray->rotspeed / 2)
		- data->ray->planey * sin(data->ray->rotspeed / 2);
	data->ray->planey = oldplanex * sin(data->ray->rotspeed / 2)
		+ data->ray->planey * cos(data->ray->rotspeed / 2);
}
