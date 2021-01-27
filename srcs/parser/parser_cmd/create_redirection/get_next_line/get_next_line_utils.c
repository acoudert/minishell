/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 16:47:25 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"

t_list_bis	*ft_lstnew(int fd)
{
	t_list_bis	*curr;

	if (!(curr = (t_list_bis*)gc_malloc((sizeof(t_list_bis)))))
		return (0);
	if (!(curr->str = (char*)gc_malloc(sizeof(char) * 1)))
		return (0);
	curr->next = 0;
	*(curr->str) = 0;
	curr->fd = fd;
	return (curr);
}

char		*ft_strchr(char *s, int c)
{
	char			*s_cpy;
	char			c_cpy;

	if (!s)
		return (0);
	s_cpy = s;
	c_cpy = (char)c;
	while (*s_cpy != c_cpy && *s_cpy)
		s_cpy++;
	return ((*s_cpy == c_cpy) ? s_cpy : 0);
}
