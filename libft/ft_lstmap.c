/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:00:43 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/29 12:08:24 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *l, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_element;

	if (l == 0 || f == 0 || del == 0)
		return (NULL);
	new_element = ft_lstnew(f(l->content));
	if (!new_element)
	{
		ft_lstclear(&l, del);
		return (NULL);
	}
	new_list = new_element;
	l = l->next;
	while (l)
	{
		new_element = ft_lstnew(f(l->content));
		if (!new_element)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_element);
		l = l->next;
	}
	return (new_list);
}
