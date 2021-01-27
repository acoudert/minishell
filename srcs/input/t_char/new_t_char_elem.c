/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_t_char_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:35:27 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:35:27 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	define_col_row_nb(t_char *cmd
		, int i, int screen_size)
{
	if (cmd[i - 1].col_nb == screen_size
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

void				new_t_char_elem(t_char *cmd, char c)
{
	int	i;
	int	screen_size;

	i = cmd[0].pos->i;
	screen_size = tigetnum("cols");
	cmd[i].key = c;
	if (i == 0)
	{
		cmd[i].row_nb = 1;
		cmd[i].col_nb = cmd[i].pos->prompt_size + 1;
	}
	else
		define_col_row_nb(cmd, i, screen_size);
}
