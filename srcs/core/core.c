/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:01:55 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "errors.h"
#include <sys/wait.h>

volatile pid_t	g_child_pid = -1;

void			extract_or_and(t_data *data, int d)
{
	while (data->cmd->or != NULL)
	{
		data->cmd = data->cmd->or;
		if (WEXITSTATUS(data->ret_code) != 0 && (d < 0 || d >
			data->cmd->depth))
		{
			core_run_target(data);
			return ;
		}
		if (d < 0)
			d *= -1;
	}
	while (data->cmd->and != NULL)
	{
		data->cmd = data->cmd->and;
		if (WEXITSTATUS(data->ret_code) == 0 && (d < 0 || d >
			data->cmd->depth))
		{
			core_run_target(data);
			return ;
		}
		if (d < 0)
			d *= -1;
	}
}

void			next_cmd(t_data *data, pid_t pid, t_core_command *ccmd, int d)
{
	d *= -1;
	if ((*ccmd).stdout_fd != STDOUT_FILENO)
		close((*ccmd).stdout_fd);
	if (data->cmd->pipe != NULL)
	{
		data->cmd = data->cmd->pipe;
		core_run_target(data);
	}
	if (data->cmd->builtin == NONE)
		waitpid(pid, &data->ret_code, 0);
	extract_or_and(data, d);
}

void			un_to_ccmd(t_core_command *ccmd)
{
	if (ccmd->stdin_fd != STDIN_FILENO)
		close(ccmd->stdin_fd);
	if (ccmd->stdout_fd != STDOUT_FILENO)
		close(ccmd->stdout_fd);
}

void			skip(t_data *data, int d)
{
	int	ch;

	d *= -1;
	ch = 0;
	while (data->cmd->pipe != NULL)
		data->cmd = data->cmd->pipe;
	while (WEXITSTATUS(data->ret_code) == 0 && data->cmd->or != NULL &&
		(d < 0 || d > data->cmd->or->depth))
	{
		data->cmd = data->cmd->or;
		if (d < 0)
			d *= -1;
		ch = 1;
	}
	while (WEXITSTATUS(data->ret_code) != 0 && data->cmd->and != NULL &&
		(d < 0 || d > data->cmd->or->depth))
	{
		data->cmd = data->cmd->and;
		if (d < 0)
			d *= -1;
		ch = 1;
	}
	if (ch == 0)
		data->cmd = NULL;
}

void			core_run(t_data *data)
{
	t_command	*old;

	old = data->cmd;
	g_killed = 0;
	data->stdin_fd = STDIN_FILENO;
	while (data->cmd != NULL)
	{
		if (fork_if_required(data) < 0)
		{
			data->ret_code = 2;
			break ;
		}
	}
	data->cmd = old;
	g_child_pid = -1;
}
