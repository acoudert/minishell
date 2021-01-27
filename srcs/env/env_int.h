/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:25:52 by caugier           #+#    #+#             */
/*   Updated: 2021/01/15 13:26:54 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_INT_H
# define ENV_INT_H

# include "minishell.h"

extern char		**g_env;
extern char		**g_argv;
extern int		g_argc;
extern size_t	g_env_size;
extern size_t	g_env_cap;

ssize_t	env_seek(const char *key, const char **value);
void	grow_env(void);

#endif
