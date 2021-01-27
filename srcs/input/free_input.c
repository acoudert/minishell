/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:35:05 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:35:05 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				free_cmd_tab(t_char **cmd_tab, t_helper **helper)
{
	if (*cmd_tab)
		gc_free(*cmd_tab);
	*cmd_tab = 0;
	if (*helper && (*helper)->word)
		gc_free((*helper)->word);
}

static inline void	free_history(t_history *history)
{
	t_history	*prev;

	if (history == 0)
		return ;
	while (history->next)
	{
		prev = history;
		history = history->next;
		gc_free(prev->content);
		gc_free(prev);
	}
	gc_free(history->content);
	gc_free(history);
}

void				free_input(t_char **cmd_tab
		, t_helper **helper, t_data *data)
{
	free_cmd_tab(cmd_tab, helper);
	free_parser(data);
	free_history(data->history);
}
