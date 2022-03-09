/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:54:44 by rgelin            #+#    #+#             */
/*   Updated: 2021/08/31 16:31:30 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		ft_strlen(char *str);
void	ft_free(char **str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);

#endif