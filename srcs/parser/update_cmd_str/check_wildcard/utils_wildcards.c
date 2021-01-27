/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcards.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:59:35 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include "gc_malloc.h"
#include "struct.h"
#include "utils.h"

static size_t	slash_strlen(char *str)
{
	char *beg;

	beg = str;
	while (*str != '/' && *str != '\0' && *str != ' ')
		str++;
	return (str - beg);
}

t_list			*get_patterns(char *str)
{
	t_list	*beg;
	t_list	*curr;
	size_t	len;

	beg = NULL;
	while (*str != '\0' && *str != ' ')
	{
		if (*str == '/')
			str++;
		len = slash_strlen(str);
		curr = gc_malloc(sizeof(t_list));
		curr->content = gc_malloc(len + 1);
		ft_memcpy(curr->content, str, len);
		((char *)curr->content)[len] = '\0';
		curr->next = NULL;
		ft_lstadd_back(&beg, curr);
		str += len;
	}
	return (beg);
}

int				match(char *s1, char *s2)
{
	if (*s1 == '\0' && *s2 == '\0')
		return (1);
	else if (*s1 == *s2 && *s1 != '\0')
		return (match(s1 + 1, s2 + 1));
	else if (*s2 == '*' && *s1 != '\0')
		return (match(s1 + 1, s2) || match(s1 + 1, s2 + 1));
	else
		return (0);
}

void			ft_wc_addback(t_wildcard **prev, t_wildcard *wc)
{
	t_wildcard	*wc0;

	if (*prev == NULL)
	{
		*prev = wc;
	}
	wc0 = *prev;
	while (wc0->next != NULL)
		wc0 = wc0->next;
	wc0->next = wc;
}

char			*path_join(char *path, char *new)
{
	size_t	l0;
	size_t	l1;
	char	*ret;

	l0 = ft_strlen(path);
	if (l0 == 0)
		return (ft_strdup(new));
	if (path[l0 - 1] == '/')
		l0--;
	l1 = ft_strlen(new);
	ret = gc_malloc(l0 + l1 + 2);
	ft_memcpy(ret, path, l0);
	ret[l0] = '/';
	ft_memcpy(&ret[l0 + 1], new, l1);
	ret[l0 + l1 + 1] = '\0';
	return (ret);
}
