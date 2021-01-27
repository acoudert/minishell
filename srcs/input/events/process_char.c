/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:32:09 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:32:09 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_char(t_char *cmd, char c)
{
	int	i;

	i = cmd[0].pos->i;
	if (cmd[i].key == 0)
		new_t_char_elem(cmd, c);
	else
	{
		mid_t_char_elem(cmd, c);
		update_col_row_t_char(cmd);
	}
	put_cmd_tab(cmd, i);
	return (1);
}
