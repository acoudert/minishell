/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mid_t_char_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:35:25 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:35:25 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mid_t_char_elem(t_char *cmd, char c)
{
	int		i;
	char	next_c;

	i = cmd[0].pos->i;
	while (cmd[i].key)
	{
		next_c = cmd[i].key;
		cmd[i].key = c;
		c = next_c;
		i++;
	}
	cmd[i].key = c;
}
