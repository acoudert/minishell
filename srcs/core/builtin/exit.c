/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:28:30 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "minishell.h"
#include "errors.h"

static void	exit_err(t_data *data, int error)
{
	const char	*str;

	str = ft_strerror(error);
	put_err_header();
	write(STDERR_FILENO, g_builtin_str_mapper[data->cmd->builtin],
		ft_strlen(g_builtin_str_mapper[data->cmd->builtin]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, data->cmd->argv[1], ft_strlen(data->cmd->argv[1]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
}

static int	exit_int(t_data *data)
{
	size_t		argc;
	int			ret;

	argc = argv_len(data->cmd->argv);
	if (argc != 1)
	{
		errno = 0;
		ret = ft_atoi(data->cmd->argv[1]);
		if (errno != 0)
		{
			exit_err(data, EC_NARGR);
			data->ret_code = 2;
			return (0);
		}
		if (argc != 2)
		{
			data->ret_code = 1;
			return (1);
		}
		data->ret_code = ((unsigned char)ret) << 8;
	}
	write(STDERR_FILENO, "exit\n", 5);
	return (0);
}

void		ft_exit(t_data *data, int stdout_fd)
{
	(void)stdout_fd;
	if (exit_int(data) == 0 && data->cmd->pipe == NULL)
		gc_exit((unsigned char)WEXITSTATUS(data->ret_code));
}
