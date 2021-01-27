/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_displayed_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:35:51 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:35:51 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	calc_col_nb(t_char *cmd, int j)
{
	int	col_nb;

	if (j == 0)
		col_nb = cmd[0].pos->prompt_size + 1;
	else if (cmd[j - 1].key == '\n')
		col_nb = 3;
	else
		col_nb = cmd[j - 1].col_nb;
	return (col_nb + 1);
}

static inline int	erase_row(int k)
{
	while (k > 0)
	{
		write(1, " ", 1);
		write(1, LEFT, ft_strlen(LEFT));
		write(1, LEFT, ft_strlen(LEFT));
		k--;
	}
	k++;
	return (k);
}

static inline void	erase_rows_set_cursor(t_char *cmd
		, int j, int row_nb)
{
	int	k;

	while (row_nb > 0)
	{
		k = calc_col_nb(cmd, j);
		k = erase_row(k);
		if (row_nb != 1)
			write(1, TOP, ft_strlen(TOP));
		j--;
		while (j > 0 && cmd[j].row_nb == row_nb)
			j--;
		while (row_nb != 1 && k != cmd[j].col_nb)
		{
			write(1, RIGHT, ft_strlen(RIGHT));
			k++;
		}
		row_nb--;
	}
}

void				erase_displayed_cmd(t_char *cmd, int i)
{
	int	j;
	int	row_nb;

	j = i;
	while (cmd[j].key)
		j++;
	if (j == 0)
		row_nb = 1;
	else if (cmd[j - 1].key == '\n')
		row_nb = cmd[j - 1].row_nb + 1;
	else
		row_nb = cmd[j - 1].row_nb;
	erase_rows_set_cursor(cmd, j, row_nb);
}
