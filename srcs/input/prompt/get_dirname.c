/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dirname.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:35:40 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:35:40 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_dirname_execve(char *home, char *directory)
{
	char	*dirname;
	int		size;
	int		i;

	i = 0;
	while (home[i] && home[i] == directory[i])
		i++;
	if (home[i])
		size = ft_strlen(directory) + 1;
	else
		size = ft_strlen(directory) - i + 2;
	if (!(dirname = (char*)gc_malloc(sizeof(char) * size)))
		return (0);
	*dirname = 0;
	if (home[i])
		ft_strlcat(dirname, directory, size);
	else
	{
		ft_strlcat(dirname, "~", 2);
		ft_strlcat(dirname, directory + i, size);
	}
	return (dirname);
}

char	*create_dirname_getcwd(void)
{
	char	*dirname;

	if (!(dirname = (char*)gc_malloc(sizeof(char) * 512)))
		return (0);
	if (getcwd(dirname, 512) == NULL)
	{
		gc_free(dirname);
		return (NULL);
	}
	return (dirname);
}

char	*get_dirname(void)
{
	char	*home;
	char	*directory;
	char	*dirname;

	home = (char*)get_env("HOME");
	directory = (char*)get_env("PWD");
	if (!home || !directory)
	{
		if (!(dirname = create_dirname_getcwd()))
			return (ft_strdup("."));
	}
	else if (!(dirname = create_dirname_execve(home, directory)))
		return (0);
	return (dirname);
}
