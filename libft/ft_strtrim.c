/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:33:14 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/29 12:03:37 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_charset(char c, const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		end;
	int		index;
	char	*res;

	i = 0;
	index = 0;
	if (s1 == 0 || set == 0)
		return (NULL);
	end = ft_strlen(s1);
	while (in_charset(s1[i], set))
		i++;
	end--;
	while (in_charset(s1[end], set) && end >= 0)
		end--;
	if (end == -1)
		res = malloc(1);
	else if (!(res = malloc(sizeof(char) * (end - i + 2))))
		return (NULL);
	while (i <= end)
		res[index++] = s1[i++];
	res[index] = 0;
	return (res);
}
