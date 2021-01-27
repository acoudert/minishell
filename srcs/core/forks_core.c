/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:52:18 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void		child_job(t_core_command *ccmd)
{
	if (STDOUT_FILENO != ccmd->stdout_fd)
		dup2(ccmd->stdout_fd, STDOUT_FILENO);
	if (STDIN_FILENO != ccmd->stdin_fd)
		dup2(ccmd->stdin_fd, STDIN_FILENO);
	if (execve(ccmd->bin, ccmd->argv, env()) < 0)
	{
		suf_strerrno(ccmd->bin);
		if (errno == EAGAIN)
			gc_exit(127);
		gc_exit(128);
	}
}

int			core_run_target(t_data *data)
{
	t_core_command	ccmd;
	pid_t			pid;

	if (data->cmd == NULL)
		return (0);
	if (to_ccmd(data, &ccmd) < 0)
		return (-1);
	if (data->cmd->builtin == NONE)
	{
		pid = fork();
		if (pid < 0)
			fatal_errno();
		g_child_pid = pid;
		if (pid == 0)
			child_job(&ccmd);
		else
			next_cmd(data, pid, &ccmd, data->cmd->depth);
	}
	else
	{
		run_builtin(data, ccmd.stdout_fd);
		next_cmd(data, -1, &ccmd, data->cmd->depth);
	}
	un_to_ccmd(&ccmd);
	return (0);
}

int			do_fork(t_data *data)
{
	g_child_pid = fork();
	if (g_child_pid < 0)
	{
		suf_strerrno("fork");
		return (-1);
	}
	if (g_child_pid != 0)
	{
		waitpid(g_child_pid, &data->ret_code, 0);
		if (g_killed == 0)
			skip(data, data->cmd->depth);
		else
		{
			data->cmd = NULL;
			data->ret_code = 130 << 8;
		}
		return (0);
	}
	core_run_target(data);
	gc_exit(WEXITSTATUS(data->ret_code));
}

int			do_nofork(t_data *data)
{
	if (core_run_target(data) < 0)
		return (-1);
	if (g_killed != 0)
	{
		data->cmd = NULL;
		data->ret_code = 130 << 8;
	}
	else
		skip(data, data->cmd->depth);
	return (0);
}

int			fork_if_required(t_data *data)
{
	if (data->cmd->pipe != NULL)
		return (do_fork(data));
	else
		return (do_nofork(data));
}
