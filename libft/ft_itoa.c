/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 15:54:07 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/10 03:27:01 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_rev_tab(char *tab, int neg)
{
	int		i;
	char	t;
	int		len;

	i = 0;
	len = ft_strlen(tab);
	while (i < len / 2)
	{
		t = tab[i + neg];
		tab[i + neg] = tab[len - 1 - i];
		tab[len - 1 - i] = t;
		i++;
	}
}

static int		size_nb(int nb)
{
	int count;

	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		count = 1;
		nb = -nb;
	}
	while (nb > 0)
	{
		count++;
		nb /= 10;
	}
	return (count);
}

static char		*ft_putnbr_str(int nb, char *res)
{
	int		i;
	long	n;

	i = 0;
	n = nb;
	if (n < 0)
	{
		res[i++] = '-';
		n = -n;
	}
	if (n == 0)
	{
		res[0] = 0 + '0';
		return (res);
	}
	while (n > 0)
	{
		res[i++] = n % 10 + '0';
		n /= 10;
	}
	res[i] = '\0';
	return (res);
}

char			*ft_itoa(int nb)
{
	char	*res;

	if (!(res = malloc(sizeof(char) * size_nb(nb) + 1)))
		return (NULL);
	res = ft_putnbr_str(nb, res);
	if (nb < 0)
		ft_rev_tab(res, 1);
	else
		ft_rev_tab(res, 0);
	return (res);
}
