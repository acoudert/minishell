/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:07:50 by caugier           #+#    #+#             */
/*   Updated: 2021/01/26 14:54:31 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "env/env_int.h"
#include <unistd.h>
#include "errors.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	data.history = 0;
	data.cmd = 0;
	data.ret_code = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	init_env(av, ac, env);
	gc_add_cb(destroy_env, NULL);
	update_env_vars();
	setupterm("xterm-256color", 0, NULL);
	get_input(&data);
	gc_exit(WEXITSTATUS(data.ret_code));
}
