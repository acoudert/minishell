/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:42:15 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*next_i(char const *s, char c, char type)
{
	if (type == 's')
		while (*s == c && *s)
			s++;
	else
		while (*s != c && *s)
			s++;
	return ((char*)s);
}

static int		find_nb_strs(char const *s, char c)
{
	int		nb_strs;

	nb_strs = 0;
	s = next_i(s, c, 's');
	while (*s)
	{
		nb_strs++;
		s = next_i(s, c, 'c');
		s = next_i(s, c, 's');
	}
	return (nb_strs);
}

static void		cpy_substr(char const *s, char c, char *cpy)
{
	char	*s_end;

	s_end = next_i(s, c, 'c');
	while (s < s_end)
	{
		*cpy = *s;
		s++;
		cpy++;
	}
	*cpy = 0;
}

char			**ft_split(char const *s, char c)
{
	int		nb_strs;
	char	**tabl;
	int		i;

	if (!s)
		return (0);
	nb_strs = find_nb_strs(s, c);
	if (!(tabl = (char**)gc_malloc(sizeof(char*) * (nb_strs + 1))))
		return (0);
	i = 0;
	s = next_i(s, c, 's');
	while (*s)
	{
		if (!(tabl[i] = (char*)gc_malloc(sizeof(char) *
				((next_i(s, c, 'c') - s) + 1))))
			return (0);
		cpy_substr(s, c, tabl[i]);
		s = next_i(s, c, 'c');
		s = next_i(s, c, 's');
		i++;
	}
	tabl[i] = 0;
	return (tabl);
}
