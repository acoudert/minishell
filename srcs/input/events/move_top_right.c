/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_top_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:32:05 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:32:05 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	move_top_right(t_char *cmd, int i)
{
	int	j;
	int	k;

	j = i;
	while (j > 0 && cmd[j].row_nb > 1
			&& cmd[j].row_nb == cmd[i].row_nb)
		j--;
	k = cmd[i].col_nb;
	while (cmd[i].row_nb > 1 && k > 1)
	{
		write(1, LEFT, ft_strlen(LEFT));
		k--;
	}
	if (cmd[i].row_nb > 1)
		write(1, TOP, ft_strlen(TOP));
	k = cmd[j].col_nb;
	while (cmd[i].row_nb > 1 && k > 1)
	{
		write(1, RIGHT, ft_strlen(RIGHT));
		k--;
	}
	return (j - i);
}
