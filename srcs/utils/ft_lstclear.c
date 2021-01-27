/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:38:00 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_lstclear_internal(t_list *lst, void (*del)(void*))
{
	if (lst == NULL)
		return ;
	ft_lstclear_internal(lst->next, del);
	del(lst->content);
	gc_free(lst);
}

void		ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (lst == NULL)
		return ;
	ft_lstclear_internal(*lst, del);
	*lst = NULL;
}
