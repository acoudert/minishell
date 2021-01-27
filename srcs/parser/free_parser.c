/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:29:27 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 10:29:29 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	free_t_redirection(t_redirection *dir)
{
	t_redirection	*prev;

	while (dir)
	{
		prev = dir;
		dir = dir->next;
		if (prev->path)
			gc_free(prev->path);
		gc_free(prev);
	}
}

void				free_t_command(t_command *cmd)
{
	int	i;

	if (cmd == 0)
		return ;
	if (cmd->bin)
	{
		gc_free(cmd->bin);
		cmd->bin = 0;
		i = 0;
		if (cmd->argv)
		{
			while (cmd->argv[i])
			{
				gc_free(cmd->argv[i]);
				i++;
			}
			gc_free(cmd->argv);
		}
		cmd->argv = 0;
	}
	free_t_redirection(cmd->stdout);
	free_t_redirection(cmd->stdin);
}

void				free_parser(t_data *data)
{
	t_command	*cmd;

	if (data->cmd == 0)
		return ;
	while (data->cmd)
	{
		cmd = data->cmd;
		if (data->cmd->pipe)
			data->cmd = data->cmd->pipe;
		else if (data->cmd->or)
			data->cmd = data->cmd->or;
		else if (data->cmd->and)
			data->cmd = data->cmd->and;
		else
			data->cmd = 0;
		free_t_command(cmd);
		gc_free(cmd);
	}
}
