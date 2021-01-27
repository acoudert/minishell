/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:33:35 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:33:35 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	put_str_color(char *str, char *color)
{
	int	size;

	write(STDERR_FILENO, color, ft_strlen(color));
	size = write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, NC, ft_strlen(NC));
	return (size);
}

int					put_prompt(void)
{
	int		size;
	char	*hostname;
	char	*dirname;

	if (!get_env("USER"))
		size = put_str_color("user42", GREEN);
	else
		size = put_str_color((char*)get_env("USER"), GREEN);
	size += put_str_color("@", GREEN);
	hostname = get_hostname();
	size += put_str_color(hostname, GREEN);
	gc_free(hostname);
	size += write(STDERR_FILENO, ":", 1);
	if (!(dirname = get_dirname()))
		size += put_str_color(".", BLUE);
	else
	{
		size += put_str_color(dirname, BLUE);
		gc_free(dirname);
	}
	size += write(STDERR_FILENO, "$ ", 2);
	return (size);
}
