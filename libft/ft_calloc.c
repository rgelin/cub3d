/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:05:06 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/09 18:20:30 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;
	size_t	i;

	i = 0;
	tab = malloc(size * count);
	if (!tab)
		return (NULL);
	while (i < count * size)
		((char *)tab)[i++] = 0;
	return (tab);
}
