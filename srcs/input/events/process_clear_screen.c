/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_clear_screen.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:32:12 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:32:12 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_clear_screen(t_char *cmd)
{
	int		pid;
	char	*argv[2];
	int		i;

	pid = fork();
	if (pid == 0)
	{
		argv[0] = "/usr/bin/clear";
		argv[1] = 0;
		execve(argv[0], argv, env());
	}
	waitpid(pid, NULL, 0);
	cmd[0].pos->prompt_size = put_prompt();
	put_cmd_tab(cmd, 0);
	if (cmd[0].key == 0)
		return ;
	i = 1;
	while (i != cmd[0].pos->i)
	{
		move_right(cmd, i);
		i++;
	}
}
