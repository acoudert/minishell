/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:29:38 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:29:38 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	get_end_quote_str(char *str, int i)
{
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '\'' || str[i] == '"')
			i += ft_next_quote(str + i);
		i++;
	}
	return (i);
}

static inline int	get_argv_size(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == 0)
			break ;
		if (str[i] == '\'' || str[i] == '"')
			i = get_end_quote_str(str, i);
		while (str[i] && str[i] != ' ')
			i++;
		size++;
	}
	return (size);
}

static char			*get_argv_member(char *str, int ret_code)
{
	int		i;
	int		j;
	char	*ret_str;

	i = 0;
	j = get_end_quote_str(str, i);
	if (!(ret_str = (char*)gc_malloc(sizeof(char) * (j + 1))))
		return (0);
	*ret_str = 0;
	ft_strlcat(ret_str, str, j + 1);
	ret_str = update_quote_str(ret_str, ret_code);
	return (ret_str);
}

static char			**create_argv_members(char *str, int size, int ret_code)
{
	char	**argv;
	int		argv_i;
	int		i;

	if (!(argv = (char**)gc_malloc(sizeof(char*) * (size + 1))))
		return (0);
	i = 0;
	argv_i = 0;
	while (str[i] && argv_i < size)
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == 0)
			break ;
		if (!(argv[argv_i] = get_argv_member(str + i, ret_code)))
			return (0);
		if (str[i] == '\'' || str[i] == '"')
			i = get_end_quote_str(str, i);
		else
			while (str[i] && str[i] != ' ')
				i++;
		argv_i++;
	}
	argv[argv_i] = 0;
	return (argv);
}

char				**create_argv(char *str, int ret_code)
{
	int		size;
	char	**argv;

	size = get_argv_size(str);
	if (!(argv = create_argv_members(str, size, ret_code)))
		return (0);
	return (argv);
}
