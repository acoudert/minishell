/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_top.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:32:03 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:32:03 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	calc_row_col_nb(t_char *cmd, int i
		, int *col_nb, int *row_nb)
{
	if (cmd[i].key)
	{
		*row_nb = cmd[i].row_nb;
		*col_nb = cmd[i].col_nb;
	}
	else if (cmd[i - 1].key == '\n')
	{
		*row_nb = cmd[i - 1].row_nb + 1;
		*col_nb = 3;
	}
	else
	{
		*row_nb = cmd[i - 1].row_nb;
		*col_nb = cmd[i - 1].col_nb + 1;
	}
}

int					move_top(t_char *cmd, int i)
{
	int	j;
	int	k;
	int	col_nb;
	int	row_nb;

	if (i == 0 || cmd[i].row_nb == 1
			|| (cmd[i].key == 0 && cmd[i - 1].row_nb == 1))
		return (0);
	calc_row_col_nb(cmd, i, &col_nb, &row_nb);
	j = i;
	while (j > 0 && cmd[j].row_nb != row_nb - 1)
		j--;
	while (j > 0 && cmd[j].col_nb > col_nb)
		j--;
	k = i;
	while (k > j)
	{
		move_left(cmd, k);
		k--;
	}
	return (j - i);
}
