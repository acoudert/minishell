/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 22:11:46 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 23:44:31 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include <string.h>
#include <errno.h>
#include "minishell.h"

char	*g_binary = NULL;

static inline void	get_binary(void)
{
	const char	**av;
	char		*str;
	char		*prev;

	if (g_binary != NULL)
		return ;
	av = argv(NULL);
	str = (char *)av[0];
	prev = str;
	while (*str != '\0')
	{
		if (*str == '/' && *(str + 1) != '\0')
			prev = str + 1;
		str++;
	}
	g_binary = prev;
}

const char			*ft_strerror(int error)
{
	size_t				i;
	const char			*ptr;
	extern const char	binary_assets_errors_bin_start_[];

	if (error < 0)
		error = EC_UNK;
	ptr = (const char *)&binary_assets_errors_bin_start_;
	i = 0;
	while (*ptr != 8)
	{
		if (i == (size_t)error)
			return (ptr);
		if (*(ptr++) == '\0')
			i++;
	}
	return (ft_strerror(EC_UNK));
}

void				put_err_header(void)
{
	get_binary();
	write(STDERR_FILENO, RED, ft_strlen(RED));
	write(STDERR_FILENO, g_binary, ft_strlen(g_binary));
	write(STDERR_FILENO, ": ", 2);
}

void				put_err(int error)
{
	const char	*str;

	str = ft_strerror(error);
	put_err_header();
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, NC, ft_strlen(NC));
}

void				put_strerrno(void)
{
	const char	*str;

	str = strerror(errno);
	put_err_header();
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, NC, ft_strlen(NC));
}
