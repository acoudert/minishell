/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 17:23:04 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include <errno.h>
#include <string.h>
#include "minishell.h"

void	fatal(int error)
{
	put_err(error);
	gc_exit(-1);
}

void	fatal_errno(void)
{
	put_strerrno();
	gc_exit(-1);
}

void	builtin_error(t_builtin builtin, int error)
{
	const char	*str;

	str = ft_strerror(error);
	put_err_header();
	write(STDERR_FILENO, g_builtin_str_mapper[builtin],
		ft_strlen(g_builtin_str_mapper[builtin]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, NC, ft_strlen(NC));
}

void	builtin_errno(t_builtin builtin)
{
	const char	*str;

	str = strerror(errno);
	put_err_header();
	write(STDERR_FILENO, g_builtin_str_mapper[builtin],
		ft_strlen(g_builtin_str_mapper[builtin]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, NC, ft_strlen(NC));
}
