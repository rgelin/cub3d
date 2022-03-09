/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:00:43 by rgelin            #+#    #+#             */
/*   Updated: 2020/12/08 12:41:37 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *l, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_element;

	if (l == 0 || f == 0 || del == 0)
		return (NULL);
	if (!(new_element = ft_lstnew(f(l->content))))
	{
		ft_lstclear(&l, del);
		return (NULL);
	}
	new_list = new_element;
	l = l->next;
	while (l)
	{
		if (!(new_element = ft_lstnew(f(l->content))))
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_element);
		l = l->next;
	}
	return (new_list);
}
