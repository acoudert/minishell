/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:34:11 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:34:11 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	process_standard_event(t_char **cmd, char *buf)
{
	if (buf[0] == 127)
		cmd[0]->pos->i += process_del(*cmd, cmd[0]->pos->i);
	else if (buf[0] == 4)
		return ;
	else if (buf[0] == '\n' && cmd_end(*cmd, buf))
		return ;
	else if ((buf[0] >= 32 && buf[0] <= 126) || buf[0] == '\n')
		cmd[0]->pos->i += process_char(*cmd, buf[0]);
}

static inline void	process_simple_event(t_char **cmd
		, char *buf, t_data *data)
{
	if (buf[2] == 'A' || buf[2] == 'B')
		history(data, cmd, cmd[0]->pos->i, buf);
	else if (buf[2] == 'C')
		cmd[0]->pos->i += move_right(*cmd, cmd[0]->pos->i);
	else if (buf[2] == 'D')
		cmd[0]->pos->i += move_left(*cmd, cmd[0]->pos->i);
	else if (buf[2] == 'F')
		cmd[0]->pos->i += move_end(*cmd, cmd[0]->pos->i);
	else if (buf[2] == 'H')
		cmd[0]->pos->i += move_home(*cmd, cmd[0]->pos->i);
	else if (buf[2] == '2')
		cmd[0]->pos->i += paste_word(*cmd, cmd[0]->pos->i);
	else if (buf[2] == '3')
		cmd[0]->pos->i += cut_word(*cmd, cmd[0]->pos->i);
	else if (buf[2] == '6')
		cmd[0]->pos->i += copy_word(*cmd, cmd[0]->pos->i);
	else if (buf[2] == '5')
		process_clear_screen(*cmd);
}

static inline void	process_advanced_event(t_char **cmd, char *buf)
{
	if (buf[5] == 'A')
		cmd[0]->pos->i += move_top(*cmd, cmd[0]->pos->i);
	else if (buf[5] == 'B')
		cmd[0]->pos->i += move_bot(*cmd, cmd[0]->pos->i);
	else if (buf[5] == 'C')
		cmd[0]->pos->i += jump_word_right(*cmd, cmd[0]->pos->i);
	else if (buf[5] == 'D')
		cmd[0]->pos->i += jump_word_left(*cmd, cmd[0]->pos->i);
}

char				*process_input(char *buf, t_char **cmd, t_helper *helper,
	t_data *data)
{
	if (!(t_char_update_size(cmd, helper)))
		return (0);
	if ((buf[0] >= 32 && buf[0] <= 127) || buf[0] == 4 || buf[0] == '\n')
		process_standard_event(cmd, buf);
	else if ((buf[2] >= 'A' && buf[2] <= 'D') || buf[2] == 'H'
			|| buf[2] == 'F' || buf[2] == '5' || buf[2] == '6'
			|| buf[2] == '3' || buf[2] == '2')
		process_simple_event(cmd, buf, data);
	else if (buf[5] >= 'A' && buf[5] <= 'D')
		process_advanced_event(cmd, buf);
	return (0);
}
