/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:32:07 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:32:07 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	paste_word(t_char *cmd, int i)
{
	int		j;
	int		k;
	char	*word;

	(void)i;
	if (cmd[0].pos->word[0] == 0)
		return (0);
	word = cmd[0].pos->word;
	j = 0;
	while (word[j])
	{
		cmd[0].pos->i += process_char(cmd, word[j]);
		j++;
	}
	k = j;
	while (j-- > 0)
		cmd[0].pos->i -= 1;
	gc_free(word);
	if (!(word = (char*)gc_malloc(sizeof(char))))
		return (0);
	*word = 0;
	cmd[0].pos->word = word;
	return (k);
}
