/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:30:07 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:30:07 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_next_quote(char *str)
{
	int		i;
	char	c;

	c = str[0];
	i = 1;
	while (str[i] && str[i] != c)
	{
		if (str[i] == '\\' && str[i + 1] == '\\')
			i++;
		else if (str[i] == '\\' && str[i + 1] == c && c == '"')
			i++;
		i++;
	}
	return (i);
}
