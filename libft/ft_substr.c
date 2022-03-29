/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:18:03 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/29 12:03:21 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;
	char	*str;

	i = 0;
	str = (char *)s;
	if (s == 0)
		return (0);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	if (start >= ft_strlen(str))
	{
		res[0] = 0;
		return (res);
	}
	while (i < len && str[i])
	{
		res[i] = str[start + i];
		i++;
	}
	res[i] = 0;
	return (res);
}
