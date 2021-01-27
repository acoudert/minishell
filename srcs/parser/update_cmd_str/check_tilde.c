/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tilde.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:34:18 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 11:55:17 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*update_tilde(char *str, int i)
{
	char	*tilde_str;
	char	*tilde_cmd_str;

	tilde_str = (char*)get_env("HOME");
	if (!tilde_str)
		return (str);
	if (!(tilde_cmd_str = (char*)gc_malloc(sizeof(char) * (
			ft_strlen(str) + ft_strlen(tilde_str)))))
		return (0);
	*tilde_cmd_str = 0;
	ft_strlcat(tilde_cmd_str, str, i + 1);
	ft_strlcat(tilde_cmd_str, tilde_str, i + ft_strlen(tilde_str) + 1);
	ft_strlcat(tilde_cmd_str, str + i + 1,
		ft_strlen(str) + ft_strlen(tilde_str));
	gc_free(str);
	return (tilde_cmd_str);
}

char	*check_tilde(char *str, int i)
{
	if (i > 0
			&& str[i] == '~'
			&& (str[i - 1] == ' ' || str[i - 1] == 0)
			&& (str[i + 1] == ' ' || str[i + 1] == 0))
		str = update_tilde(str, i);
	return (str);
}
