/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:29:40 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 14:39:32 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_directory(char *str, char *dir_path)
{
	char			*ret_str;
	DIR				*directory;
	struct dirent	*dir_struct;
	size_t			size;

	ret_str = 0;
	if (!(directory = opendir(dir_path)))
		return (0);
	gc_add_cb((void *)closedir, directory);
	while (!ret_str && (dir_struct = readdir(directory)))
	{
		if (ft_strcmp(dir_struct->d_name, str) == 0)
		{
			size = ft_strlen(dir_path) + 1 + ft_strlen(str) + 1;
			if (!(ret_str = gc_malloc(sizeof(char) * size)))
				return (0);
			*ret_str = 0;
			ft_strlcat(ret_str, dir_path, size);
			ft_strlcat(ret_str, "/", size);
			ft_strlcat(ret_str, str, size);
		}
	}
	gc_rm_cb((void *)closedir, directory);
	closedir(directory);
	return (ret_str);
}

void	free_path(char **path)
{
	int	i;

	if (path == 0)
		return ;
	i = 0;
	while (path[i])
	{
		gc_free(path[i]);
		i++;
	}
	gc_free(path);
}

char	*create_bin(char *str)
{
	char	*ret_str;
	char	*path_env_str;
	char	**path;
	int		i;

	ret_str = 0;
	if (!(path_env_str = (char*)get_env("PATH")))
		return (ft_strdup(str));
	path = ft_split(path_env_str, ':');
	i = 0;
	while (path[i])
	{
		if (ret_str == NULL)
			ret_str = check_directory(str, path[i]);
		i++;
	}
	free_path(path);
	if (ret_str == 0)
		ret_str = ft_strdup(str);
	return (ret_str);
}
