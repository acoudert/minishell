/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:15:09 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"
#include <stdlib.h>

t_gc_list	*list_pop(t_gc_list **list)
{
	t_gc_list	*ret;

	ret = *list;
	if (ret != NULL)
		*list = ret->next;
	return (ret);
}

void		list_push_front(t_gc_list **list, t_gc_list *elem)
{
	elem->next = *list;
	*list = elem;
}
