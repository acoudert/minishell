/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:39:41 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void (*const g_builtin_fn_mapper[])(t_data *data, int stdout_fd) = {ft_cd,
	ft_export, ft_unset, ft_exit};
const char	*g_builtin_str_mapper[] = {"cd", "export", "unset", "exit"};

void	run_builtin(t_data *data, int stdout_fd)
{
	g_builtin_fn_mapper[data->cmd->builtin](data, stdout_fd);
}

size_t	argv_len(char **argv)
{
	char	**orig;

	orig = argv;
	while (*argv != NULL)
		argv++;
	return (argv - orig);
}
