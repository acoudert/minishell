/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chevron.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:34:42 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 11:55:17 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	*update_chevron(char *str, int *i)
{
	int	j;

	j = 0;
	if (str[*i] == str[*i + 1])
		j = 1;
	if (((*i > 0 && (str[*i - 1] != ' ' || str[*i + j + 1] != ' ')))
			|| (*i == 0 && str[*i + j + 1] != ' '))
		str = put_surrounding_char(str, *i, *i + j, ' ');
	(*i)++;
	while (str[*i] != ' ')
		(*i)++;
	(*i)--;
	return (str);
}

char				*check_chevron(char *str, int *i)
{
	if (str[*i] == '>' || str[*i] == '<')
		str = update_chevron(str, i);
	return (str);
}
