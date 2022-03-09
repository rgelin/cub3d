/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:21:23 by rgelin            #+#    #+#             */
/*   Updated: 2020/11/19 17:11:41 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	res;
	char	*str;

	i = 0;
	j = 0;
	res = ft_strlen((char *)src);
	str = (char *)src;
	while (dst[i])
		i++;
	if (i < size)
		res += i;
	else
		res += size;
	while (str[j] && i + 1 < size)
	{
		dst[i] = str[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (res);
}
