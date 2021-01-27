/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prev_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:30:09 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:30:32 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_prev_quote(char *str, int i)
{
	char	c;
	int		j;

	c = str[i];
	j = i - 1;
	while (j > 0 && ((str[j - 1] == '\\' && str[j] == c) || str[j] != c))
		j--;
	return (i - j);
}
