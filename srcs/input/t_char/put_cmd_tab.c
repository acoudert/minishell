/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_cmd_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:35:29 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:35:29 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	fill_spaces(int space_nb)
{
	while (space_nb > 0)
	{
		write(1, " ", 1);
		space_nb--;
	}
}

static inline void	put_cmd_tab_lines(t_char *cmd
		, int screen_size, int *i)
{
	char	c;

	while (cmd[*i].key)
	{
		c = cmd[*i].key;
		if (c == '\n')
		{
			if (*i > 0)
				fill_spaces(screen_size - cmd[*i].col_nb + 1);
			else
				fill_spaces(screen_size -
						cmd[0].pos->prompt_size - 1);
			write(1, "\n", 1);
			write(1, "> ", 2);
		}
		else if (cmd[*i].row_nb < cmd[*i + 1].row_nb)
		{
			write(1, &c, 1);
			write(1, "\n", 1);
		}
		else
			write(1, &c, 1);
		(*i)++;
	}
}

void				put_cmd_tab(t_char *cmd, int i)
{
	int	screen_size;
	int	space_nb;
	int	j;

	j = i;
	screen_size = tigetnum("cols");
	put_cmd_tab_lines(cmd, screen_size, &i);
	if (i > 0)
		space_nb = screen_size - cmd[i - 1].col_nb - 1;
	else
		space_nb = screen_size - cmd[0].pos->prompt_size;
	while (space_nb > 0)
	{
		write(1, " ", 1);
		write(1, LEFT, ft_strlen(LEFT));
		space_nb--;
	}
	while (i > j + 1)
	{
		move_left(cmd, i);
		i--;
	}
}
