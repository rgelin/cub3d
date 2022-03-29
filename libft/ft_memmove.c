/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:20:02 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/29 12:07:23 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*a;
	unsigned char	*b;

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
