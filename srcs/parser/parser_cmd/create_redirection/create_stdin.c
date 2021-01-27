/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stdin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:29:22 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:29:22 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_stdin(t_command *elem, char *str, int ret_code)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			if (!(create_stdin_double(elem, str + i, ret_code)))
				return (0);
			i++;
		}
		else if (str[i] == '<')
		{
			if (!(create_stdin_simple(elem, str + i, ret_code)))
				return (0);
		}
		if (str[i] == '"' || str[i] == '\'')
			i += ft_next_quote(str + i);
		i++;
	}
	return (1);
}
