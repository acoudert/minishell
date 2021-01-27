/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:21:15 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 10:21:17 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*
** free_parser.c
*/
void			free_parser(t_data *data);

/*
** quotes/
*/
char			*update_quote_str(char *str, int ret_code);
char			*update_single_quote_str(char *str, int *i);
char			*update_double_quote_str(char *str, int *i, int ret_code);
int				ft_prev_quote(char *str, int i);
int				ft_next_quote(char *str);
int				find_next_index_jump_quotes(char *str);
void			ft_remove_empty_quotes(char *str);

/*
** update_cmd_str/
*/

char			*update_cmd_str(char *str, int ret_code);
char			*put_surrounding_char(char *str, int i0, int i1, char c);
char			*check_var(char *str, int i, int ret_code);
char			*check_tilde(char *str, int i);
char			*check_chevron(char *str, int *i);
char			*check_backslash(char *str, int *i);
int				check_quote(char *str);

/*
** update_cmd_str/check_wildcard/
*/

char			*check_wildcard(char *str, int i);
char			*expand_wildcards(char *str);

/*
** parser_cmd/
*/

void			parser_cmd(t_data *data, t_cmd_chain *cmd_lst);
char			*create_bin(char *str);
int				create_builtin(char *str);
char			**create_argv(char *str, int ret_code);

/*
** parser_cmd/create_redirection/
*/

int				create_redirection(t_command *elem, char *str, int ret_code);
t_redirection	*create_redirection_elem(int type, char *path);
char			*redirection_filename(char *str, int ret_code);
int				create_stdin(t_command *elem, char *str, int ret_code);
int				create_stdin_simple(t_command *elem, char *str, int ret_code);
int				create_stdin_double(t_command *elem, char *str, int ret_code);
int				create_stdout(t_command *elem, char *str, int ret_code);
int				get_next_line(int fd, char **line);

/*
** parser_cmd_chain.c
*/

int				parser_cmd_chain(t_data *data, char *cmd_chain);

/*
** parser_cmd_chains.c
*/

void			parser_cmd_chains(t_data *data, char *cmd_chains);

/*
**  utils_wildcards.c
*/
size_t			slash_strlen(char *str);
t_list			*get_patterns(char *str);
int				match(char *s1, char *s2);
void			ft_wc_addback(t_wildcard **prev, t_wildcard *wc);
char			*path_join(char *path, char *new);

/*
** expand_wildcards.c
*/
void			expand_wc(t_wildcard *wc);

/*
** update_wildcard.c
*/
t_wildcard		*update_t_wildcard(t_wildcard **wc, struct dirent *s);
void			expand_wc(t_wildcard *wc);
char			*quote_wc(char *str);
void			fill_wc(char *str, t_wildcard *wc);

#endif
