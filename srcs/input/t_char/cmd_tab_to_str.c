/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:32:59 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:33:22 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	cmd_tab_str_size(t_char *cmd_tab)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (cmd_tab[i].key)
	{
		if ((cmd_tab[i].key == '"' || cmd_tab[i].key == '\'')
			&& (i == 0 || cmd_tab[i - 1].key != '\\'))
		{
			i += find_next_cmd_tab_quote(cmd_tab + i) + 1;
			size += i;
		}
		else if (cmd_tab[i].key == '\n')
			i++;
		else
		{
			i++;
			size++;
		}
	}
	return (size);
}

static inline void	cpy_cmd_tab_quotes(int *i, int *j
		, t_char *cmd_tab, char *str)
{
	char	c;

	c = cmd_tab[*i].key;
	str[*j] = cmd_tab[*i].key;
	(*i)++;
	(*j)++;
	while (cmd_tab[*i].key && (cmd_tab[*i].key != c
		|| (cmd_tab[*i].key == c
		&& cmd_tab[*i - 1].key == '\\')))
	{
		str[*j] = cmd_tab[*i].key;
		(*i)++;
		(*j)++;
	}
}

static inline void	cpy_cmd_tab_to_str(t_char *cmd_tab
		, char *str, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < size)
	{
		if (cmd_tab[i].key == '\n')
			i++;
		else if ((cmd_tab[i].key == '"' || cmd_tab[i].key == '\'')
				&& (i == 0 || cmd_tab[i - 1].key != '\\'))
			cpy_cmd_tab_quotes(&i, &j, cmd_tab, str);
		str[j] = cmd_tab[i].key;
		i++;
		j++;
	}
	str[j] = 0;
}

char				*cmd_tab_to_str(t_char *cmd_tab)
{
	char	*str;
	int		size;

	size = cmd_tab_str_size(cmd_tab);
	if (!(str = (char*)gc_malloc(sizeof(char) * (size + 1))))
		return (0);
	cpy_cmd_tab_to_str(cmd_tab, str, size);
	return (str);
}
