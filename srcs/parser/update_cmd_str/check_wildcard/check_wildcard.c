/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:35:23 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 11:55:17 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			found_wildcard(char *str, int i)
{
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

static inline char	*wildcard_update_cmd_str(char *str
		, int i, char *wildcard_str)
{
	char	*buffer;
	int		size_old;
	int		size_new;
	int		total_size;

	size_old = 0;
	while (str[i + size_old] && str[i + size_old] != ' ')
		size_old++;
	size_new = ft_strlen(wildcard_str);
	total_size = ft_strlen(str) + size_new - size_old + 2;
	buffer = str;
	if (!(str = (char*)gc_malloc(sizeof(char) * total_size)))
		return (0);
	*str = 0;
	ft_strlcat(str, buffer, i + 1);
	ft_strlcat(str, wildcard_str, total_size);
	ft_strlcat(str, buffer + i + size_old, total_size);
	gc_free(buffer);
	return (str);
}

static inline char	*update_str_wildcard(char *str, int i)
{
	char	*wildcard_str;

	if (!(wildcard_str = expand_wildcards(str + i)))
		return (str);
	if (*wildcard_str)
		str = wildcard_update_cmd_str(str, i, wildcard_str);
	gc_free(wildcard_str);
	return (str);
}

char				*check_wildcard(char *str, int i)
{
	if (!found_wildcard(str, i))
		return (str);
	str = update_str_wildcard(str, i);
	return (str);
}
