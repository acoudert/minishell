/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:51:56 by caugier           #+#    #+#             */
/*   Updated: 2021/01/26 18:58:10 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int		open_stdout(t_data *data, t_core_command *ccmd)
{
	t_redirection	*redir;
	int				fd;

	fd = -1;
	redir = data->cmd->stdout;
	while (redir != NULL)
	{
		if (fd != -1)
			close(fd);
		if (redir->type == r_simple)
			fd = open(redir->path, O_WRONLY | O_TRUNC | O_CREAT, 0664);
		else
			fd = open(redir->path, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (fd < 0)
		{
			suf_strerrno(redir->path);
			return (-1);
		}
		redir = redir->next;
	}
	ccmd->stdout_fd = fd;
	return (0);
}

int		plop(t_data *data, t_redirection **redir, int *fds)
{
	if (fds[0] != -1)
		close(fds[0]);
	if ((*redir)->type == r_simple)
		fds[0] = open((*redir)->path, O_RDONLY);
	else
	{
		if (pipe(fds) < 0)
		{
			suf_strerrno("pipe");
			return (-1);
		}
		if (write(fds[1], data->cmd->stdin->path,
			ft_strlen(data->cmd->stdin->path)) < 0)
		{
			suf_strerrno("write");
			return (-1);
		}
		close(fds[1]);
	}
	if (fds[0] < 0)
		suf_strerrno((*redir)->path);
	if (fds[0] < 0)
		return (-1);
	*redir = (*redir)->next;
	return (0);
}

int		open_stdin(t_data *data, t_core_command *ccmd)
{
	t_redirection	*redir;
	int				fds[2];

	fds[0] = -1;
	redir = data->cmd->stdin;
	while (redir != NULL)
	{
		if (plop(data, &redir, fds) < 0)
			return (-1);
	}
	ccmd->stdin_fd = fds[0];
	return (0);
}

int		to_ccmd(t_data *data, t_core_command *ccmd)
{
	int	fds[2];

	ccmd->bin = data->cmd->bin;
	ccmd->argv = data->cmd->argv;
	ccmd->stdin_fd = data->stdin_fd;
	ccmd->stdout_fd = STDOUT_FILENO;
	if (data->cmd->pipe != NULL)
	{
		if (pipe(fds) < 0)
		{
			suf_strerrno("pipe");
			return (-1);
		}
		ccmd->stdout_fd = fds[1];
		data->stdin_fd = fds[0];
	}
	if (data->cmd->stdin != NULL)
		if (open_stdin(data, ccmd) < 0)
			return (-1);
	if (data->cmd->stdout != NULL)
		if (open_stdout(data, ccmd) < 0)
			return (-1);
	return (0);
}
