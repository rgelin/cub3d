/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:20:02 by rgelin            #+#    #+#             */
/*   Updated: 2020/12/08 12:35:54 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *a;
	unsigned char *b;

	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	if (len == 0 || dst == src)
		return (dst);
	if (dst > src)
	{
		while (len)
		{
			a[len - 1] = b[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(a, b, len);
	return (dst);
}
