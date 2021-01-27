/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stdin_double.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:31:19 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 10:31:20 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			*get_stdin_input_str(char *word)
{
	char	*str;
	char	*line;
	char	*buffer;

	if (!(str = (char*)gc_malloc(sizeof(char))))
		return (0);
	*str = 0;
	while (1)
	{
		line = 0;
		write(STDOUT_FILENO, "> ", 2);
		get_next_line(STDIN_FILENO, &line);
		if (!(ft_strcmp(line, word)))
			break ;
		buffer = str;
		str = ft_strjoin(str, line);
		str = ft_strjoin(str, "\n");
		gc_free(buffer);
		gc_free(line);
	}
	return (str);
}

static inline int	stdin_double_word_start_index(char *str, int *i)
{
	str[*i] = ' ';
	str[*i + 1] = ' ';
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (str[*i] == 0)
		return (0);
	return (1);
}

int					create_stdin_double(t_command *elem, char *str,
	int ret_code)
{
	int				i;
	char			*word;
	char			*input_str;
	t_redirection	*curr;

	i = 0;
	if (!stdin_double_word_start_index(str, &i))
		return (0);
	if (!(word = redirection_filename(str + i, ret_code)))
	{
		syntax_error();
		return (0);
	}
	if (!(input_str = get_stdin_input_str(word)))
		return (0);
	if (elem->stdin == 0)
		elem->stdin = create_redirection_elem(r_double, input_str);
	else
	{
		curr = elem->stdin;
		while (curr->next)
			curr = curr->next;
		curr->next = create_redirection_elem(r_simple, input_str);
	}
	return (1);
}
