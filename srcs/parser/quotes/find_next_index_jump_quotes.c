/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_next_index_jump_quotes.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:30:04 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:30:04 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_next_index_jump_quotes(char *str)
{
	int		i;
	char	c;

	c = str[0];
	i = 1;
	while (str[i] && ((str[i - 1] == '\\' && str[i] == c) || str[i] != c))
		i++;
	if (str[i] == 0)
		return (i);
	return (i + 1);
}
