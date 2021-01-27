/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_surrounding_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:35:05 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 11:55:17 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*put_surrounding_char(char *str, int i0, int i1, char c)
{
	int		i;
	char	*ret_str;

	i = ft_strlen(str);
	if (!(ret_str = (char*)gc_malloc(sizeof(char) * (i + 3))))
		return (0);
	i = -1;
	while (++i < i0)
		ret_str[i] = str[i];
	ret_str[i] = c;
	while (i <= i1)
	{
		ret_str[i + 1] = str[i];
		i++;
	}
	ret_str[i + 1] = c;
	while (str[i])
	{
		ret_str[i + 2] = str[i];
		i++;
	}
	ret_str[i + 2] = 0;
	gc_free(str);
	return (ret_str);
}
