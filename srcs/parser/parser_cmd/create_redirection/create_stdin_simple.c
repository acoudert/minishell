/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stdin_simple.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:31:57 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 10:31:59 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_stdin_simple(t_command *elem, char *str, int ret_code)
{
	int				i;
	char			*filename;
	t_redirection	*curr;

	i = 0;
	str[i] = ' ';
	while (str[i] == ' ')
		i++;
	if (!(filename = redirection_filename(str + i, ret_code)))
	{
		syntax_error();
		return (0);
	}
	if (elem->stdin == 0)
		elem->stdin = create_redirection_elem(r_simple, filename);
	else
	{
		curr = elem->stdin;
		while (curr->next)
			curr = curr->next;
		curr->next = create_redirection_elem(r_simple, filename);
	}
	return (1);
}
