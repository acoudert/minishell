/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_quote_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:30:17 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:30:17 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*update_quote_str(char *str, int ret_code)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			if (!(str =
				update_double_quote_str(str, &i, ret_code)))
				return (0);
		}
		else if (str[i] == '\'')
			str = update_single_quote_str(str, &i);
		i++;
	}
	return (str);
}
