/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 03:05:56 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/10 18:56:06 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_perror(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	ft_free(t_data *data)
{
	int i;
	
	i = -1;
	while (data->data && data->data[++i])
		free(data->data[i]);
	if (data->data)
		free(data->data);
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

