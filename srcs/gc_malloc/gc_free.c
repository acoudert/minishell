/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 15:25:45 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_malloc_int.h"
#include "errors.h"

static void	*ft_free_int(void *ptr, t_gc_list *lst)
{
	void	*ret;

	if (lst == NULL)
		return (NULL);
	if (lst->content == ptr)
	{
		free(ptr);
		ret = lst->next;
		park(lst);
		if (ret == NULL)
			return ((void *)1);
		return (ret);
	}
	ret = ft_free_int(ptr, lst->next);
	if (ret == NULL)
		return (NULL);
	if (ret == (void *)1)
		ret = NULL;
	lst->next = ret;
	return (lst);
}

void		gc_free(void *ptr)
{
	void	*ret;

	if (ptr == NULL)
		return ;
	ret = ft_free_int(ptr, g_pointers);
	if (ret == NULL)
		fatal(EC_ILLF);
	if (ret == (void *)1)
		ret = NULL;
	g_pointers = ret;
}
