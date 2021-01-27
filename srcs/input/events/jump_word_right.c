/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_word_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:31:46 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:31:46 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	jump_word_right(t_char *cmd, int i)
{
	int	j;
	int	k;

	if (cmd[i].key == 0)
		return (0);
	j = i;
	while (cmd[j].key && !ft_alphanum(cmd[j].key))
		j++;
	while (cmd[j].key && ft_alphanum(cmd[j].key))
		j++;
	k = i;
	while (k < j)
	{
		move_right(cmd, k);
		k++;
	}
	return (j - i);
}
