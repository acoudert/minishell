/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stdout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:31:29 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 10:31:31 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	stdout_word_start_index(char *str, int *i, int type)
{
	str[*i] = ' ';
	if (type == r_double)
		str[*i + 1] = ' ';
	while (str[*i] == ' ')
		(*i)++;
}

static int			create_stdout_elem(t_command *elem, char *str
		, int ret_code, int type)
{
	int				i;
	char			*filename;
	t_redirection	*curr;

	i = 0;
	stdout_word_start_index(str, &i, type);
	if (!(filename = redirection_filename(str + i, ret_code)))
	{
		syntax_error();
		return (0);
	}
	if (elem->stdout == 0)
		elem->stdout = create_redirection_elem(type, filename);
	else
	{
		curr = elem->stdout;
		while (curr->next)
			curr = curr->next;
		curr->next = create_redirection_elem(type, filename);
	}
	curr = elem->stdout;
	return (1);
}

int					create_stdout(t_command *elem, char *str, int ret_code)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
		{
			if (!(create_stdout_elem(elem, str + i
					, ret_code, r_double)))
				return (0);
			i++;
		}
		else if (str[i] == '>')
		{
			if (!(create_stdout_elem(elem, str + i
					, ret_code, r_simple)))
				return (0);
		}
		if (str[i] == '"' || str[i] == '\'')
			i += ft_next_quote(str + i);
		i++;
	}
	return (1);
}
