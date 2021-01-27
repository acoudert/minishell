/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:31:08 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 10:31:09 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection		*create_redirection_elem(int type, char *path)
{
	t_redirection *elem;

	if (!(elem = (t_redirection*)gc_malloc(sizeof(t_redirection))))
		return (0);
	elem->type = type;
	elem->path = path;
	elem->next = 0;
	return (elem);
}

static inline int	create_redirection_elems(t_command *elem
		, char *str, int ret_code)
{
	if (!(create_stdout(elem, str, ret_code)))
	{
		syntax_error();
		return (0);
	}
	if (!(create_stdin(elem, str, ret_code)))
	{
		syntax_error();
		return (0);
	}
	return (1);
}

static inline int	check_redirection_error(t_redirection *curr)
{
	if (curr->path == 0)
	{
		syntax_error();
		return (0);
	}
	return (1);
}

int					create_redirection(t_command *elem, char *str, int ret_code)
{
	t_redirection *curr;

	elem->stdin = 0;
	elem->stdout = 0;
	if (!(create_redirection_elems(elem, str, ret_code)))
		return (0);
	curr = elem->stdin;
	while (curr)
	{
		if (!(check_redirection_error(curr)))
			return (0);
		curr = curr->next;
	}
	curr = elem->stdout;
	while (curr)
	{
		if (!(check_redirection_error(curr)))
			return (0);
		curr = curr->next;
	}
	return (1);
}
