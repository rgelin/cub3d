/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:15:44 by rgelin            #+#    #+#             */
/*   Updated: 2020/11/23 14:56:36 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list	*ptr;

	if (!(ptr = malloc(sizeof(t_list))))
		return (NULL);
	ptr->content = content;
	ptr->next = 0;
	return (ptr);
}
