/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:39:22 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/23 17:51:25 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	if (s1 == 0 || s2 == 0)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (s1[++i])
		res[i] = ((char *)s1)[i];
	while (s2[++j])
		res[i + j] = ((char *)s2)[j];
	res[i + j] = 0;
	return (res);
}
