/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ext_itoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:28:49 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_my_mod(int a, int b)
{
	int r;

	r = a % b;
	return (r < 0 ? 10 - r - b : r);
}

static int	ft_digit_count(int n)
{
	int count;

	if (n == 0)
		return (n);
	count = 0;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	int		i;
	char	*res;

	if (n == 0)
		return (ft_strdup("0"));
	i = n >= 0 ? ft_digit_count(n) : ft_digit_count(n) + 1;
	res = gc_malloc(i + 1);
	res[i] = '\0';
	while (n != 0)
	{
		res[--i] = (char)(ft_my_mod(n, 10) + '0');
		n /= 10;
	}
	if (i == 1)
		res[0] = '-';
	return (res);
}
