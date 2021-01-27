/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:21:02 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 10:21:05 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

extern t_data	**g_data;
extern t_char	**g_cmd_tab;
extern t_helper	**g_helper;

/*
** tty_mode.c
*/
void	tty_raw_setup(void);
void	tty_default_setup(void);

/*
** prompt/
*/
int		put_prompt(void);
char	*get_dirname(void);
char	*get_hostname(void);

/*
** t_char.c
*/
int		t_char_update_size(t_char **cmd_tab, t_helper *helper);
void	t_char_set_zeros(t_char *cmd_tab, t_helper *helper);
void	new_t_char_elem(t_char *cmd, char c);
void	mid_t_char_elem(t_char *cmd, char c);

/*
** erase_displayed_cmd.c
*/
void	erase_displayed_cmd(t_char *cmd, int i);

/*
** cmd_tab.c
*/
char	*cmd_tab_to_str(t_char *cmd_tab);
int		find_next_cmd_tab_quote(t_char *cmd);
void	update_col_row_t_char(t_char *cmd);
void	put_cmd_tab(t_char *cmd, int i);

/*
** history.c
*/
int		update_history(t_data *data, char *cmd_str);
void	history(t_data *data, t_char **cmd, int i, char *buf);

/*
** free_input.c
*/
void	free_cmd_tab(t_char **cmd_tab, t_helper **helper);
void	free_input(t_char **cmd_tab, t_helper **helper, t_data *data);

/*
**  events/
*/
int		move_bot(t_char *cmd, int i);
int		move_top(t_char *cmd, int i);
int		move_end(t_char *cmd, int i);
int		move_home(t_char *cmd, int i);
int		jump_word_left(t_char *cmd, int i);
int		jump_word_right(t_char *cmd, int i);
int		paste_word(t_char *cmd, int i);
int		cut_word(t_char *cmd, int i);
int		copy_word(t_char *cmd, int i);
int		move_right(t_char *cmd, int i);
int		move_left(t_char *cmd, int i);
int		process_char(t_char *cmd, char c);
int		process_del(t_char *cmd, int i);
int		move_top_right(t_char *cmd, int i);
int		move_bot_left(t_char *cmd, int i);
void	process_clear_screen(t_char *cmd);

/*
** process_input.c
*/
char	*process_input(char *buf, t_char **cmd
		, t_helper *helper, t_data *data);

/*
** cmd_end.c
*/
char	cmd_end(t_char *cmd_tab, char *buf);

/*
** get_input.c
*/
void	helper_setup(t_data *data, t_helper *helper);
int		get_input(t_data *data);

#endif
