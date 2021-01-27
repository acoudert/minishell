/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:31:49 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:31:49 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	calc_row_col_nb(t_char *cmd, int i
		, int *col_nb, int *row_nb)
{
	if (cmd[i].key != '\n')
	{
		*row_nb = cmd[i].row_nb;
		*col_nb = cmd[i].col_nb;
	}
	else
	{
		*row_nb = cmd[i - 1].row_nb;
		*col_nb = cmd[i].col_nb;
	}
}

int					move_bot(t_char *cmd, int i)
{
	int	j;
	int	k;
	int	col_nb;
	int	row_nb;

	if (cmd[i].key == 0)
		return (0);
	calc_row_col_nb(cmd, i, &col_nb, &row_nb);
	j = i;
	while (cmd[j].key && cmd[j].row_nb != row_nb + 1)
		j++;
	while (cmd[j].key && cmd[j].col_nb < col_nb)
		j++;
	if (cmd[j].key == 0 && cmd[j - 1].row_nb == row_nb)
		return (0);
	k = i;
	while (k < j)
	{
		move_right(cmd, k);
		k++;
	}
	return (j - i);
}
