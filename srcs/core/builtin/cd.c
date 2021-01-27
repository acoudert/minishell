/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:49:02 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"
#include "errors.h"

static int	do_chdir(const char *path)
{
	char	*cwd;

	if (chdir(path) < 0)
	{
		builtin_errno(CD);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		write(STDERR_FILENO, "cd: ", 4);
		cwd = (char *)ft_strerror(EC_GCWD);
		write(STDERR_FILENO, cwd, ft_strlen(cwd));
		write(STDERR_FILENO, ": getcwd: ", 10);
		cwd = strerror(errno);
		write(STDERR_FILENO, cwd, ft_strlen(cwd));
		write(STDERR_FILENO, "\n", 1);
	}
	else
	{
		set_env("PWD", cwd);
		free(cwd);
	}
	return (0);
}

void		ft_cd(t_data *data, int stdout_fd)
{
	size_t		argc;
	const char	*home;

	(void)stdout_fd;
	argc = argv_len(data->cmd->argv);
	data->ret_code = 1;
	if (argc > 3)
		builtin_error(data->cmd->builtin, EC_TMARGS);
	else if (argc == 2)
		data->ret_code = do_chdir(data->cmd->argv[1]);
	else
	{
		home = get_env("HOME");
		if (home != NULL)
			data->ret_code = do_chdir(home);
		else
			builtin_error(data->cmd->builtin, EC_HOMEUNST);
	}
}
