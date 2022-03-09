/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:50:46 by rgelin            #+#    #+#             */
/*   Updated: 2020/11/23 17:19:37 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*ptr;

	ptr = *alst;
	if (alst == 0 || new == 0)
		return ;
	if (ptr == 0)
		*alst = new;
	else
	{
		while (ptr->next != 0)
			ptr = ptr->next;
		ptr->next = new;
		new->next = 0;
	}
}
