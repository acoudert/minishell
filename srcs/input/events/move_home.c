/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_home.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:31:57 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:31:57 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	move_home(t_char *cmd, int i)
{
	int	j;
	int	k;
	int	row_nb;

	j = i;
	if (j == 0)
		return (0);
	else if (cmd[j].key != 0)
		row_nb = cmd[i].row_nb;
	else
		row_nb = cmd[j - 1].row_nb;
	while (j > 0 && (j - 1 == 0 || cmd[j - 1].row_nb == row_nb))
		j--;
	k = i;
	while (k > j)
	{
		move_left(cmd, k);
		k--;
	}
	return (j - i);
}
