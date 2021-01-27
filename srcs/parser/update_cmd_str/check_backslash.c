/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_backslash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:34:06 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 11:55:17 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	*update_backslash(char *str, int i)
{
	int	j;

	j = i;
	while (str[j])
	{
		str[j] = str[j + 1];
		j++;
	}
	str = put_surrounding_char(str, i, i, '\'');
	return (str);
}

char				*check_backslash(char *str, int *i)
{
	if (str[*i] == '\\' && str[*i + 1] != '\'')
	{
		str = update_backslash(str, *i);
		(*i) += 2;
	}
	else if (str[*i] == '\\' && str[*i + 1] == '\'')
	{
		str = put_surrounding_char(str, *i, *i + 1, '"');
		(*i) += 3;
	}
	return (str);
}
