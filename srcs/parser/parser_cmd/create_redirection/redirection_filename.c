/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_filename.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:31:38 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 11:55:17 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	update_str(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '<' && str[i] != '>')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			j = ft_next_quote(str + i);
			i += j;
			while (j >= 0)
			{
				str[j] = ' ';
				j--;
			}
		}
		str[i] = ' ';
		i++;
	}
}

char				*redirection_filename(char *str, int ret_code)
{
	int		i;
	int		j;
	char	*filename;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '<' && str[i] != '>')
	{
		if (str[i] == '\'' || str[i] == '"')
			i += ft_next_quote(str + i);
		i++;
	}
	if (!(filename = (char*)gc_malloc(sizeof(char) * (i + 1))))
		return (0);
	j = 0;
	while (j < i)
	{
		filename[j] = str[j];
		str[j] = ' ';
		j++;
	}
	filename[j] = 0;
	if (!(filename = update_quote_str(filename, ret_code)))
		return (0);
	update_str(str);
	return (filename);
}
