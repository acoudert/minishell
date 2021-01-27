/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:32:01 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:32:01 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	move_right(t_char *cmd, int i)
{
	int	screen_size;

	screen_size = tigetnum("cols");
	if (cmd[i].key == 0)
		return (0);
	else if (cmd[i].key == '\n')
		return (move_bot_left(cmd, i));
	else if (cmd[i].col_nb == screen_size)
		return (move_bot_left(cmd, i));
	write(1, RIGHT, ft_strlen(RIGHT));
	return (1);
}
