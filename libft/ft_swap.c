/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:55:23 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/22 17:03:26 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(char *res)
{
	int		i;
	char	temp;

	i = 0;
	while (i < (int)ft_strlen(res) / 2)
	{
		temp = res[i];
		res[i] = res[ft_strlen(res) - i - 1];
		res[ft_strlen(res) - i - 1] = temp;
		i++;
	}
}
