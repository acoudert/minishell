/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cmd_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:34:32 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 11:55:17 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*update_cmd_str(char *str, int ret_code)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		str = check_var(str, i, ret_code);
		str = check_tilde(str, i);
		str = check_chevron(str, &i);
		if (str[i] == '"' || str[i] == '\'')
		{
			j = check_quote(str + i);
			if (j == 0)
				continue;
			else
				i += j;
		}
		str = check_backslash(str, &i);
		str = check_wildcard(str, i);
		i++;
	}
	return (str);
}
