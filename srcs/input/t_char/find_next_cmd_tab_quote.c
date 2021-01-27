/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_next_cmd_tab_quote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:35:21 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:35:21 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_next_cmd_tab_quote(t_char *cmd)
{
	int		i;
	char	c;

	c = cmd[0].key;
	i = 1;
	while (cmd[i].key && cmd[i].key != c)
	{
		if (cmd[i].key == '\\' && cmd[i + 1].key == '\\')
			i++;
		else if (cmd[i].key == '\\' && cmd[i + 1].key == c && c == '"')
			i++;
		i++;
	}
	return (i);
}
