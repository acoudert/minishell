/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 15:25:47 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "gc_malloc_int.h"

void	*gc_malloc(size_t n)
{
	void		*ptr;
	t_gc_list	*lst;

	lst = unpark();
	ptr = malloc(n);
	if (ptr == NULL)
		fatal(EC_NOMEM);
	lst->content = ptr;
	lst->next = NULL;
	list_push_front(&g_pointers, lst);
	return (ptr);
}
