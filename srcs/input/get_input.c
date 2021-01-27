/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:35:00 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 11:50:23 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data				**g_data;
t_char				**g_cmd_tab;
t_helper			**g_helper;

inline void			helper_setup(t_data *data, t_helper *helper)
{
	helper->prompt_size = put_prompt();
	helper->t_char_size = 512;
	helper->i = 0;
	helper->word = 0;
	if (!(helper->word = (char*)gc_malloc(sizeof(char))))
		return ;
	helper->word[0] = 0;
	helper->history = data->history;
}

static inline void	get_input_setup(char *buf
		, char **cmd, t_char **cmd_tab)
{
	buf[6] = 0;
	*cmd = 0;
	*cmd_tab = 0;
}

static inline void	call_parser(t_char **cmd_tab, t_data *data
		, char **cmd, t_helper *helper)
{
	int	i;

	i = (*cmd_tab)[0].pos->i;
	while ((*cmd_tab)[i].key)
		i += move_right(*cmd_tab, i);
	tty_default_setup();
	*cmd = cmd_tab_to_str(*cmd_tab);
	update_history(data, *cmd);
	parser_cmd_chains(data, *cmd);
	free_cmd_tab(cmd_tab, &helper);
	free_parser(data);
	gc_free(*cmd);
	helper_setup(data, helper);
}

int					get_input(t_data *data)
{
	t_char		*cmd_tab;
	char		*cmd;
	char		buf[7];
	t_helper	helper;
	t_helper	*pt_helper;

	g_data = &data;
	g_cmd_tab = &cmd_tab;
	pt_helper = &helper;
	g_helper = &pt_helper;
	get_input_setup(buf, &cmd, &cmd_tab);
	tty_raw_setup();
	helper_setup(data, &helper);
	while (read(0, buf, 7) && (buf[0] != 4
			|| (buf[0] == 4 && cmd_tab != 0 && cmd_tab[0].key)))
	{
		process_input(buf, &cmd_tab, &helper, data);
		if (cmd_end(cmd_tab, buf) && buf[0] != 4)
			call_parser(&cmd_tab, data, &cmd, &helper);
		tty_raw_setup();
	}
	free_input(&cmd_tab, &pt_helper, data);
	write(STDERR_FILENO, "exit", 4);
	tty_default_setup();
	return (0);
}
