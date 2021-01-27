/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:39:09 by caugier           #+#    #+#             */
/*   Updated: 2021/01/26 12:13:59 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_killed;

void			handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		if (g_child_pid == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			free_cmd_tab(g_cmd_tab, g_helper);
			helper_setup(*g_data, *g_helper);
		}
		else if (g_child_pid != 0)
		{
			g_killed = 1;
			kill(g_child_pid, SIGINT);
		}
		else
			gc_exit(130);
	}
}

void			handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		if (g_child_pid > 0)
		{
			g_killed = 1;
			kill(g_child_pid, SIGQUIT);
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		}
		else if (g_child_pid != -1)
		{
			gc_exit(130);
		}
	}
}
