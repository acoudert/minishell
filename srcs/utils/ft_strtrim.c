/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:02:18 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	nb_char_to_trim(char const *s1, char const *set, int direction)
{
	int		i;
	int		i_res;

	i = 0;
	i_res = 0;
	if (direction < 0)
	{
		i_res = 0;
		while (s1[i_res])
			i_res++;
		if (i_res > 0)
			i_res--;
	}
	while (set[i])
		if (s1[i_res] == set[i])
		{
			(direction > 0) ? i_res++ : i_res--;
			i = 0;
		}
		else
			i++;
	return (i_res);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		i;
	int		len;

	if (!s1 || !set)
		return (0);
	i = nb_char_to_trim(s1, set, 1);
	s1 += i;
	len = nb_char_to_trim(s1, set, -1) + 1;
	if (!(trimmed = (char*)gc_malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while (i < len)
	{
		trimmed[i] = s1[i];
		i++;
	}
	trimmed[i] = 0;
	return (trimmed);
}
