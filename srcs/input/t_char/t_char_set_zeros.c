/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_char_set_zeros.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:35:31 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:35:31 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_char_set_zeros(t_char *cmd_tab, t_helper *helper)
{
	int	i;

	i = 0;
	while (i < helper->t_char_size)
	{
		cmd_tab[i].key = 0;
		cmd_tab[i].row_nb = 0;
		cmd_tab[i].col_nb = 0;
		cmd_tab[i].pos = helper;
		i++;
	}
}
