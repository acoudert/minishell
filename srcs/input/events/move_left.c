/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_left.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:31:59 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:31:59 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	move_left(t_char *cmd, int i)
{
	if (i == 0)
		return (0);
	else if (cmd[i - 1].key == '\n')
		return (move_top_right(cmd, i));
	else if (cmd[i].col_nb == 1)
		return (move_top_right(cmd, i));
	write(1, LEFT, ft_strlen(LEFT));
	return (-1);
}
