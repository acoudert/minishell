/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_add_cb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 23:17:37 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:24:30 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_malloc_int.h"
#include "errors.h"

t_gc_list	*g_callbacks = NULL;

void	gc_add_cb(void (*cb)(void *), void *param)
{
	t_gc_list	*lst;
	t_callback	*cb_struct;

	lst = unpark();
	lst->next = NULL;
	cb_struct = malloc(sizeof(t_callback));
	if (cb_struct == NULL)
		fatal(EC_NOMEM);
	cb_struct->func = cb;
	cb_struct->param = param;
	lst->content = cb_struct;
	list_push_front(&g_callbacks, lst);
}
