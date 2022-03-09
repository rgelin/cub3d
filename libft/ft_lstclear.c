/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:00:51 by rgelin            #+#    #+#             */
/*   Updated: 2020/11/23 20:24:40 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*temp;

	ptr = *lst;
	temp = *lst;
	if (lst == 0 || del == 0 || *lst == 0)
		return ;
	while (ptr)
	{
		temp = temp->next;
		del(ptr->content);
		free(ptr);
		ptr = temp;
	}
	*lst = 0;
}
