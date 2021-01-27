/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_char_update_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:35:33 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:35:33 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline t_char	*t_char_init(t_helper *helper)
{
	t_char	*cmd_tab;
	int		i;

	if (!(cmd_tab = (t_char*)gc_malloc(sizeof(t_char) * helper->t_char_size)))
		return (0);
	i = 0;
	while (i < helper->t_char_size)
	{
		cmd_tab[i].key = 0;
		cmd_tab[i].row_nb = 0;
		cmd_tab[i].col_nb = 0;
		cmd_tab[i].pos = helper;
		i++;
	}
	return (cmd_tab);
}

static inline void		t_char_copy(t_char *dest, t_char *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dest[i].key = src[i].key;
		dest[i].row_nb = src[i].row_nb;
		dest[i].col_nb = src[i].col_nb;
		dest[i].pos = src[i].pos;
		i++;
	}
}

int						t_char_update_size(t_char **cmd_tab, t_helper *helper)
{
	t_char	*ret;
	int		i;

	if (*cmd_tab == 0)
	{
		if (!(*cmd_tab = t_char_init(helper)))
			return (0);
	}
	i = 0;
	while (i + 1 < helper->t_char_size && (*cmd_tab)[i].key)
		i++;
	if (i + 1 == helper->t_char_size)
	{
		helper->t_char_size += 512;
		if (!(ret = t_char_init(helper)))
			return (0);
		t_char_copy(ret, *cmd_tab, helper->t_char_size - 512);
		gc_free(*cmd_tab);
		*cmd_tab = ret;
	}
	return (1);
}
