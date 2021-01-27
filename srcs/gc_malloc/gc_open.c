/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 22:58:35 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_malloc_int.h"
#include <fcntl.h>
#include "minishell.h"
#include "errors.h"

t_gc_list	*g_files = NULL;

int	gc_open(const char *path, int mode)
{
	int			fd;
	t_gc_list	*lst;

	lst = unpark();
	fd = open(path, mode);
	if (fd < 0)
		fatal(EC_CNTOPEN);
	lst->content = (void *)(unsigned long long)fd;
	lst->next = NULL;
	list_push_front(&g_files, lst);
	return (fd);
}
