/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:30:45 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 14:39:32 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command			*ft_create_cmd_elem(t_cmd_chain *elem, int ret_code)
{
	t_command	*cmd_elem;

	if (!(cmd_elem = (t_command*)gc_malloc(sizeof(t_command))))
		return (0);
	if (!(create_redirection(cmd_elem, elem->cmd_str, ret_code)))
		return (0);
	cmd_elem->argv = create_argv(elem->cmd_str, ret_code);
	cmd_elem->builtin = create_builtin(cmd_elem->argv[0]);
	cmd_elem->bin = 0;
	if (cmd_elem->builtin == NONE)
		cmd_elem->bin = create_bin(cmd_elem->argv[0]);
	cmd_elem->depth = elem->parenthesis_depth;
	cmd_elem->pipe = 0;
	cmd_elem->or = 0;
	cmd_elem->and = 0;
	return (cmd_elem);
}

static inline int	parser_cmd_elems(t_cmd_chain *cmd_lst
		, t_cmd_chain *elem, t_data *data)
{
	if (!(cmd_lst))
		return (0);
	if (!(cmd_lst->cmd_str = update_cmd_str(cmd_lst->cmd_str, data->ret_code)))
	{
		syntax_error();
		return (0);
	}
	if (!(data->cmd = ft_create_cmd_elem(elem, data->ret_code)))
		return (0);
	return (1);
}

static inline int	create_next_cmd_elem(t_data *data
		, t_command **curr_cmd, t_cmd_chain *elem)
{
	if (elem->next_op == PIPE)
	{
		(*curr_cmd)->pipe = ft_create_cmd_elem(elem->next, data->ret_code);
		*curr_cmd = (*curr_cmd)->pipe;
	}
	else if (elem->next_op == AND)
	{
		(*curr_cmd)->and = ft_create_cmd_elem(elem->next, data->ret_code);
		*curr_cmd = (*curr_cmd)->and;
	}
	else if (elem->next_op == OR)
	{
		(*curr_cmd)->or = ft_create_cmd_elem(elem->next, data->ret_code);
		*curr_cmd = (*curr_cmd)->or;
	}
	else
		return (0);
	return (1);
}

void				parser_cmd(t_data *data, t_cmd_chain *cmd_lst)
{
	t_cmd_chain	*elem;
	t_command	*curr_cmd;

	elem = cmd_lst;
	if (!(parser_cmd_elems(cmd_lst, elem, data)))
		return ;
	curr_cmd = data->cmd;
	while (elem && elem->next)
	{
		if (!create_next_cmd_elem(data, &curr_cmd, elem))
			break ;
		elem = elem->next;
	}
}
