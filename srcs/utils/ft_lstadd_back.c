/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:33:16 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_lstadd_back_internal(t_list *alst, t_list *new)
{
	if (alst == NULL)
		return ;
	if (alst->next == NULL)
	{
		alst->next = new;
		return ;
	}
	ft_lstadd_back_internal(alst->next, new);
}

void		ft_lstadd_back(t_list **alst, t_list *new)
{
	if (alst == NULL)
		return ;
	if (new == NULL)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	ft_lstadd_back_internal(*alst, new);
}
