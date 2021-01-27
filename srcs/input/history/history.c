/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:35:55 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:35:55 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					update_history(t_data *data, char *cmd_str)
{
	t_history	*elem;
	int			i;

	if (!cmd_str || *cmd_str == 0 ||
			(cmd_str[0] == '\n' && ft_strlen(cmd_str) == 1))
		return (0);
	i = 0;
	while (data->history && cmd_str[i] && data->history->content[i] &&
			cmd_str[i] == data->history->content[i])
	{
		i++;
		if (!cmd_str[i] && !data->history->content[i])
			return (-1);
	}
	if (!(elem = (t_history*)gc_malloc(sizeof(t_history))))
		return (0);
	elem->content = ft_strdup(cmd_str);
	elem->next = data->history;
	if (data->history)
		data->history->prec = elem;
	else
		elem->prec = 0;
	data->history = elem;
	return (1);
}

static inline void	history_display(t_data *data
		, t_char **cmd, int i, char *buf)
{
	int	j;

	erase_displayed_cmd(*cmd, i);
	t_char_set_zeros(*cmd, cmd[0]->pos);
	cmd[0]->pos->i = 0;
	j = 0;
	cmd[0]->pos->prompt_size = put_prompt();
	while (cmd[0]->pos->history->content[j])
	{
		buf[0] = cmd[0]->pos->history->content[j];
		process_input(buf, cmd, cmd[0]->pos, data);
		j++;
	}
}

void				history(t_data *data, t_char **cmd, int i, char *buf)
{
	char	*cmd_str;

	if (data->history == 0)
		return ;
	else if (buf[2] == 'B' && cmd[0]->pos->history == data->history)
		return ;
	else if (buf[2] == 'B' && cmd[0]->pos->history->prec)
		cmd[0]->pos->history = cmd[0]->pos->history->prec;
	else if (buf[2] == 'B')
		return ;
	else if (buf[2] == 'A' && cmd[0]->pos->history == data->history)
	{
		cmd_str = cmd_tab_to_str(*cmd);
		if (update_history(data, cmd_str) == -1
				&& cmd[0]->pos->history->next)
			cmd[0]->pos->history = cmd[0]->pos->history->next;
	}
	else if (buf[2] == 'A' && cmd[0]->pos->history->next)
		cmd[0]->pos->history = cmd[0]->pos->history->next;
	else if (buf[2] == 'A')
		return ;
	history_display(data, cmd, i, buf);
}
