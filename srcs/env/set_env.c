/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:17:17 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_int.h"
#include "minishell.h"

char	*get_str(const char *key, const char *value)
{
	size_t	l0;
	size_t	l1;
	char	*ret;

	l0 = ft_strlen(key);
	l1 = ft_strlen(value);
	ret = gc_malloc(sizeof(*ret) * (l0 + l1 + 2));
	ft_memcpy(ret, key, l0);
	ret[l0] = '=';
	ft_memcpy(&ret[l0 + 1], value, l1);
	ret[l0 + l1 + 1] = '\0';
	return (ret);
}

void	set_env(const char *key, const char *value)
{
	ssize_t	index;

	index = env_seek(key, NULL);
	if (index == -1)
	{
		if (g_env_cap == g_env_size)
			grow_env();
		index = g_env_size;
		g_env_size++;
	}
	gc_free(g_env[index]);
	g_env[index] = get_str(key, value);
}
