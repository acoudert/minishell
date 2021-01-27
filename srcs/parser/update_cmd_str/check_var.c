/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:34:56 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 11:55:17 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_var_name(char *str)
{
	int		i;
	int		j;
	char	*var_name;

	i = 1;
	while (str[i] && str[i] != ' '
			&& (ft_alphanum(str[i]) || str[i] == '_'))
	{
		i++;
	}
	if (i == 1 && str[i] == '?')
		i++;
	if (!(var_name = (char*)gc_malloc(sizeof(char) * (i))))
		return (0);
	j = 0;
	while (j + 1 < i)
	{
		var_name[j] = str[j + 1];
		j++;
	}
	var_name[j] = 0;
	return (var_name);
}

static char	*ft_var_str(char *var_name, int ret_code, char *buffer)
{
	char	*var_str;

	if (*var_name == '?')
		var_str = ft_itoa(ret_code);
	else
	{
		if (buffer)
		{
			if (!(var_str = (char*)gc_malloc(sizeof(char) *
					(ft_strlen(buffer) + 1))))
				return (0);
			*var_str = 0;
			ft_strlcat(var_str, buffer, ft_strlen(buffer) + 1);
		}
		else
		{
			if (!(var_str = (char*)gc_malloc(sizeof(char) * 1)))
				return (0);
			*var_str = 0;
		}
	}
	return (var_str);
}

static char	*ft_var_cmd_str(char *str, int i
		, char *var_name, char *var_str)
{
	char	*var_cmd_str;

	if (!(var_cmd_str = (char*)gc_malloc(sizeof(char) *
			(ft_strlen(str) + ft_strlen(var_str) - ft_strlen(var_name) + 1))))
		return (0);
	*var_cmd_str = 0;
	ft_strlcat(var_cmd_str, str, i + 1);
	ft_strlcat(var_cmd_str, var_str, i + ft_strlen(var_str) + 1);
	ft_strlcat(var_cmd_str, str + i + ft_strlen(var_name) + 1,
		ft_strlen(str) + ft_strlen(var_str) - ft_strlen(var_name) + 1);
	return (var_cmd_str);
}

static char	*update_var(char *str, int i, int ret_code)
{
	char	*var_name;
	char	*var_str;
	char	*var_cmd_str;

	var_name = ft_var_name(str + i);
	var_str = ft_var_str(var_name, ret_code, (char*)get_env(var_name));
	if (!var_name || !var_str)
		return (0);
	var_cmd_str = ft_var_cmd_str(str, i, var_name, var_str);
	if (!var_cmd_str)
		return (0);
	gc_free(var_name);
	gc_free(var_str);
	gc_free(str);
	return (var_cmd_str);
}

char		*check_var(char *str, int i, int ret_code)
{
	if (str[i] == '$')
		str = update_var(str, i, (char)(WEXITSTATUS(ret_code)));
	return (str);
}
