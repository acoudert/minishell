/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:12:30 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 23:01:12 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <errors.h>

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v');
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int			ft_atoi(const char *nptr)
{
	int	res;
	int	sign;
	int	n;

	n = 0;
	while (ft_isspace(*(nptr++)) == 1)
		;
	nptr--;
	if (*nptr == '-')
		sign = -1;
	else
		sign = 1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	res = 0;
	while (ft_isdigit(*nptr))
	{
		res = res * 10 + sign * (*(nptr++) - '0');
		n++;
	}
	while (ft_isspace(*(nptr++)) == 1)
		;
	if (*(nptr - 1) != '\0' || n == 0)
		errno = 1;
	return (res);
}
