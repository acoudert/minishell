/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_single_quote_str.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:30:19 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:30:19 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*update_single_quote_str(char *str, int *i)
{
	int	j;
	int	k;

	k = ft_next_quote(str + *i);
	j = *i;
	while (str[j])
	{
		str[j] = str[j + 1];
		j++;
	}
	j = *i + k - 1;
	while (str[j])
	{
		str[j] = str[j + 1];
		j++;
	}
	str[j] = 0;
	*i += k - 2;
	return (str);
}
