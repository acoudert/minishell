/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:58:28 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 23:58:28 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

const char	*get_env(const char *key);
void		set_env(const char *key, const char *value);
void		del_env(const char *key);
char		**env(void);
void		init_env(char **argv, int argc, char **env);
void		destroy_env(void *param);
const char	**argv(int *argc);

#endif
