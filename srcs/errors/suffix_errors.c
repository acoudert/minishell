/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suffix_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:49:26 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include <errno.h>
#include <string.h>

void	suf_err(int error, const char *suf)
{
	const char	*str;

	str = ft_strerror(error);
	put_err_header();
	write(STDERR_FILENO, suf, ft_strlen(suf));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, NC, ft_strlen(NC));
}

void	suf_strerrno(const char *suf)
{
	const char	*str;

	str = strerror(errno);
	put_err_header();
	write(STDERR_FILENO, suf, ft_strlen(suf));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, NC, ft_strlen(NC));
}
