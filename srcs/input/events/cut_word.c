/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:31:41 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:31:41 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	cut_word_update_cmd_tab(t_char *cmd, char *word
		, int j, int k)
{
	int	l;

	l = 0;
	while (l + j < k)
	{
		word[l] = cmd[l + j].key;
		l++;
	}
	word[l] = 0;
	l = cmd[0].pos->i;
	while (l < k)
	{
		move_right(cmd, l);
		l++;
	}
	while (l > j)
	{
		process_del(cmd, l);
		l--;
	}
	return (j);
}

int					cut_word(t_char *cmd, int i)
{
	int		j;
	int		k;
	char	*word;

	j = i;
	if (!ft_alphanum(cmd[i].key))
		return (0);
	while (j > 0 && cmd[j].key != ' ' && cmd[j].key != '\n'
			&& cmd[j - 1].row_nb == cmd[j].row_nb)
		j--;
	if (cmd[j].key == ' ' || cmd[j].key == '\n')
		j++;
	k = i;
	while (cmd[k].key && cmd[k].key != ' ' && cmd[k].key != '\n')
		k++;
	if (!(word = (char*)gc_malloc(sizeof(char) * (k - j + 1))))
		return (0);
	j = cut_word_update_cmd_tab(cmd, word, j, k);
	gc_free(cmd[0].pos->word);
	cmd[0].pos->word = word;
	return (j - i);
}
