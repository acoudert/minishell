/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:24:30 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_int.h"

void	del_env(const char *key)
{
	ssize_t	index;

	index = env_seek(key, NULL);
	if (index < 0)
		return ;
	g_env_size--;
	g_env[index] = g_env[g_env_size];
	g_env[g_env_size] = NULL;
}
