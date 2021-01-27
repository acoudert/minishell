/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:58:32 by caugier           #+#    #+#             */
/*   Updated: 2021/01/26 14:54:31 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

extern volatile pid_t	g_child_pid;
extern volatile int		g_killed;
void		core_run(t_data	*data);
void		handle_sigint(int sig);
void		handle_sigquit(int sig);

/*
** fds_core.c
*/
int			open_stdout(t_data *data, t_core_command *ccmd);
int			open_stdin(t_data *data, t_core_command *ccmd);
int			to_ccmd(t_data *data, t_core_command *ccmd);

/*
** forks_core.c
*/
void		child_job(t_core_command *ccmd);
int			core_run_target(t_data *data);
int			do_fork(t_data *data);
int			do_nofork(t_data *data);
int			fork_if_required(t_data *data);

/*
** core.c
*/
void		extract_or_and(t_data *data, int d);
void		next_cmd(t_data *data, pid_t pid, t_core_command *ccmd, int d);
void		un_to_ccmd(t_core_command *ccmd);
void		skip(t_data *data, int d);

/*
** env_vars.c
*/
void		update_env_vars(void);

#endif
