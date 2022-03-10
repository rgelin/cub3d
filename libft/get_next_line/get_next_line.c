/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:54:47 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/10 04:00:11 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_copy_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str)
		return (NULL);
	line = malloc(sizeof(char) * (ft_strlen_gnl(str) + 1));
	if (!line)
		return (NULL);
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_copy_remain(char *str)
{
	int		i;
	int		j;
	char	*remain;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (NULL);
	remain = malloc(sizeof(char) * (ft_strlen_gnl(str) - i + 1));
	if (!remain)
		return (NULL);
	i += 1;
	while (str[i])
		remain[j++] = str[i++];
	remain[j] = '\0';
	return (remain);
}

static char	*ft_returned_value(char **save)
{
	int		i;
	char	*line;
	char	*temp;

	i = 0;
	if (!*save)
		return (NULL);
	if (new_line(*save))
	{
		line = ft_copy_line(*save);
		temp = ft_copy_remain(*save);
		ft_free_gnl(save);
		*save = temp;
		if ((*save)[0] == '\0')
			ft_free_gnl(save);
		return (line);
	}
	else
	{
		line = ft_strdup_gnl(*save);
		ft_free_gnl(save);
		return (line);
	}
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*save = NULL;
	int			ret;
	char		*temp;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = '\0';
		if (!save)
			save = ft_strdup_gnl(buf);
		else
		{
			temp = ft_strjoin_gnl(save, buf);
			ft_free_gnl(&save);
			save = temp;
		}
		if (new_line(buf))
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
	}
	return (ft_returned_value(&save));
}
