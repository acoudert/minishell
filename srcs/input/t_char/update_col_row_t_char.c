/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_col_row_t_char.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:35:35 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:36:06 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	update_single_elem(t_char *cmd
		, int i, int screen_size)
{
	if (i == 0)
	{
		cmd[i].row_nb = 1;
		cmd[i].col_nb = cmd[0].pos->prompt_size + 1;
	}
	else if (cmd[i - 1].col_nb == screen_size
			|| cmd[i - 1].key == '\n')
	{
		cmd[i].row_nb = cmd[i - 1].row_nb + 1;
		if (cmd[i - 1].key == '\n')
			cmd[i].col_nb = 3;
		else
			cmd[i].col_nb = 1;
	}
	else
	{
		cmd[i].row_nb = cmd[i - 1].row_nb;
		cmd[i].col_nb = cmd[i - 1].col_nb + 1;
	}
}

void				update_col_row_t_char(t_char *cmd)
{
	int	i;
	int	screen_size;

	i = cmd[0].pos->i;
	screen_size = tigetnum("cols");
	while (cmd[i].key)
	{
		update_single_elem(cmd, i, screen_size);
		i++;
	}
}
