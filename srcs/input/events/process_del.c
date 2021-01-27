/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:32:14 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:32:25 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			first_line_elem(t_char *cmd, int i)
{
	if (i == 0)
		return (1);
	else if (cmd[i].row_nb == cmd[i - 1].row_nb)
		return (0);
	else if (cmd[i].row_nb > cmd[i - 1].row_nb)
		return (1);
	else if (cmd[i - 1].key == '\n')
		return (1);
	return (0);
}

static inline void	shift_cmd_tab_key(t_char *cmd, int *i)
{
	char	c;
	char	next_c;

	c = cmd[*i].key;
	while (*i > 0 && cmd[*i].key)
	{
		next_c = cmd[*i + 1].key;
		cmd[*i - 1].key = c;
		c = next_c;
		(*i)++;
	}
	cmd[*i - 1].key = c;
}

int					process_del(t_char *cmd, int i)
{
	int	j;
	int	screen_size;

	screen_size = tigetnum("cols");
	if (i > 0 && !first_line_elem(cmd, i))
	{
		j = i;
		shift_cmd_tab_key(cmd, &i);
		update_col_row_t_char(cmd);
		write(1, LEFT, ft_strlen(LEFT));
		put_cmd_tab(cmd, j - 1);
		if (i != j && cmd[j - 1].key != '\n')
			write(1, LEFT, ft_strlen(LEFT));
		if (cmd[j - 1].key == '\n')
			move_left(cmd, j);
		else if (i > 1 && cmd[i - 2].col_nb == screen_size)
		{
			write(1, " ", 1);
			write(1, LEFT, ft_strlen(LEFT));
		}
		return (-1);
	}
	return (0);
}
