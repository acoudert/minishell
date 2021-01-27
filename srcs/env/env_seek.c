/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_seek.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:08:49 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_int.h"

static inline const char	*match_key(const char *key, const char *arg)
{
	while (*arg != '=' && *key == *arg)
	{
		arg++;
		key++;
	}
	if (*key == '\0' && *arg == '=')
		return (arg + 1);
	return (NULL);
}

ssize_t						env_seek(const char *key, const char **value)
{
	size_t		i;
	const char	*ret;

	if (value != NULL)
		*value = NULL;
	ret = NULL;
	i = 0;
	while (i < g_env_size)
	{
		ret = match_key(key, g_env[i]);
		if (ret != NULL)
		{
			if (value != NULL)
				*value = ret;
			return (i);
		}
		i++;
	}
	return (-1);
}
