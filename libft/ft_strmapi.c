/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:39:46 by rgelin            #+#    #+#             */
/*   Updated: 2020/11/27 12:55:56 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	char			*str;
	unsigned int	i;

	str = (char*)s;
	i = 0;
	if (!s || !f)
		return (NULL);
	if (!(res = malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	while (str[i])
	{
		res[i] = f(i, str[i]);
		i++;
	}
	res[i] = 0;
	return (res);
}
