/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:52:25 by caugier           #+#    #+#             */
/*   Updated: 2021/01/26 00:02:55 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/*
** utils/
*/
typedef struct				s_list {
	void					*content;
	struct s_list			*next;
}							t_list;

/*
** input/
*/
typedef struct				s_status
{
	int						depth;
	int						s_quote;
	int						d_quote;
}							t_status;

typedef struct				s_history {
	char					*content;
	struct s_history		*next;
	struct s_history		*prec;
}							t_history;

typedef struct				s_helper
{
	int						prompt_size;
	int						t_char_size;
	int						i;
	char					*word;
	t_history				*history;
}							t_helper;

typedef struct				s_char
{
	char					key;
	int						row_nb;
	int						col_nb;
	t_helper				*pos;
}							t_char;

/*
** parser/
*/
typedef enum				e_builtin {
	CD,
	EXPORT,
	UNSET,
	EXIT,
	NONE
}							t_builtin;
typedef enum				e_operator
{
	NOTHING,
	PIPE,
	AND,
	OR
}							t_operator;

typedef struct s_cmd_chain	t_cmd_chain;
struct						s_cmd_chain
{
	int						parenthesis_depth;
	char					*cmd_str;
	t_operator				next_op;
	t_cmd_chain				*next;
};

typedef struct				s_wildcard {
	struct s_wildcard		*next;
	char					*string;
	t_list					*patterns;
	char					*cwd;
}							t_wildcard;

/*
** common
*/
typedef enum				e_type {
	r_simple,
	r_double,
}							t_type;

typedef struct				s_redirection {
	t_type					type;
	char					*path;
	struct s_redirection	*next;
}							t_redirection;

typedef struct				s_command {
	char					*bin;
	char					**argv;
	t_builtin				builtin;
	struct s_command		*pipe;
	struct s_command		*or;
	struct s_command		*and;
	t_redirection			*stdout;
	t_redirection			*stdin;
	int						depth;
}							t_command;

typedef struct				s_core_command {
	char					*bin;
	char					**argv;
	int						stdin_fd;
	int						stdout_fd;
}							t_core_command;

typedef struct				s_data {
	t_command				*cmd;
	t_history				*history;
	int						stdin_fd;
	int						ret_code;
}							t_data;

#endif
