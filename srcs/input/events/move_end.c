/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:31:55 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:31:55 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	move_end(t_char *cmd, int i)
{
	int	j;
	int	k;
	int	row_nb;

	j = i;
	if (cmd[j].key == 0)
		return (0);
	else
		row_nb = cmd[j].row_nb;
	while (cmd[j].key && (cmd[j + 1].key == 0
				|| cmd[j + 1].row_nb == row_nb))
		j++;
	k = i;
	while (k < j)
	{
		move_right(cmd, k);
		k++;
	}
	return (j - i);
}
