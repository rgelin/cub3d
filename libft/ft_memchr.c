/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:00:37 by rgelin            #+#    #+#             */
/*   Updated: 2020/11/30 14:07:02 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	a;

	i = 0;
	ptr = (unsigned char *)s;
	a = (unsigned char)c;
	while (i < n)
	{
		if (a == ptr[i])
			return (&ptr[i]);
		i++;
	}
	return (NULL);
}
