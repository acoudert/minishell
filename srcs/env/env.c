/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:30:34 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 16:03:34 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_int.h"
#include "minishell.h"

char	**g_env = NULL;
char	**g_argv = NULL;
int		g_argc = 0;
size_t	g_env_size = 0;
size_t	g_env_cap = 0;

void		init_env(char **argv, int argc, char **env)
{
	size_t	i;

	if (g_env != NULL || g_argv != NULL)
		return ;
	g_argc = argc;
	g_argv = argv;
	while (env[g_env_size] != NULL)
		g_env_size++;
	g_env_cap = (g_env_size / 512 + 1) * 512;
	g_env = gc_malloc(sizeof(*g_env) * (g_env_cap + 1));
	i = 0;
	while (i < g_env_size)
	{
		g_env[i] = ft_strdup(env[i]);
		i++;
	}
	ft_memset8(&g_env[g_env_size - 1], 0, g_env_cap - g_env_size + 1);
}

void		destroy_env(void *param)
{
	size_t	i;

	(void)param;
	i = 0;
	while (i < g_env_size)
	{
		gc_free(g_env[i]);
		i++;
	}
	gc_free(g_env);
	g_env = NULL;
}

void		grow_env(void)
{
	char	**new_env;

	g_env_cap += 512;
	new_env = gc_malloc(sizeof(*new_env) * (g_env_cap + 1));
	ft_memcpy8(new_env, g_env, g_env_size);
	gc_free(g_env);
	g_env = new_env;
	ft_memset8(&g_env[g_env_size - 1], 0, g_env_cap - g_env_size + 1);
}

char		**env(void)
{
	return (g_env);
}

const char	**argv(int *argc)
{
	if (argc != NULL)
		*argc = g_argc;
	return ((const char **)g_argv);
}
