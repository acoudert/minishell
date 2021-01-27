/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_word_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:31:44 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:31:44 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	jump_word_left(t_char *cmd, int i)
{
	int	j;
	int	k;

	j = i;
	if (i > 0 && ft_alphanum(cmd[j].key))
		j--;
	while (j > 0 && !ft_alphanum(cmd[j].key))
		j--;
	while (j > 0 && ft_alphanum(cmd[j].key))
		j--;
	if (cmd[j].key == ' ' || cmd[j].key == '\n')
		j++;
	k = i;
	while (k > j)
	{
		move_left(cmd, k);
		k--;
	}
	return (j - i);
}
