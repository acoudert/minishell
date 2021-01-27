/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:50:59 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 23:50:59 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_data	t_data;
extern const char		*g_builtin_str_mapper[];
extern	void	(*const g_builtin_fn_mapper[])(t_data *data, int stdout_fd);
void		ft_cd(t_data *data, int stdout_fd);
void		ft_exit(t_data *data, int stdout_fd);
void		ft_export(t_data *data, int stdout_fd);
void		ft_unset(t_data *data, int stdout_fd);
void		run_builtin(t_data *data, int stdout_fd);
size_t		argv_len(char **argv);

#endif
