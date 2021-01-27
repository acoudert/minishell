/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bot_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:31:53 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:31:53 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	move_bot_left(t_char *cmd, int i)
{
	int	j;
	int	k;

	j = i;
	while (cmd[j].key && cmd[j].row_nb == cmd[i].row_nb)
		j++;
	k = cmd[i].col_nb;
	while (cmd[j].row_nb > cmd[i].row_nb
			&& k > 1)
	{
		write(1, LEFT, ft_strlen(LEFT));
		k--;
	}
	if (cmd[j].row_nb > cmd[i].row_nb)
		write(1, BOT, ft_strlen(BOT));
	k = cmd[j].col_nb;
	while (cmd[j].row_nb > cmd[i].row_nb && k > 1)
	{
		write(1, RIGHT, ft_strlen(RIGHT));
		k--;
	}
	return (j - i);
}
