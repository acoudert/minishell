/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_chain.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:29:46 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 14:39:32 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_chain			*ft_create_cmd_chain_elem(char *cmd_str
			, int parenthesis_depth, int size)
{
	t_cmd_chain	*elem;

	if (!(elem = (t_cmd_chain*)gc_malloc(sizeof(t_cmd_chain))))
		return (0);
	elem->parenthesis_depth = parenthesis_depth;
	if (!(elem->cmd_str = (char*)gc_malloc(sizeof(char) * (size + 1))))
		return (0);
	elem->cmd_str[0] = 0;
	ft_strlcat(elem->cmd_str, cmd_str, size + 1);
	if (cmd_str[size])
	{
		if (cmd_str[size] == '&' && cmd_str[size + 1] == '&')
			elem->next_op = AND;
		else if (cmd_str[size] == '|' && cmd_str[size + 1] == '|')
			elem->next_op = OR;
		else if (cmd_str[size] == '|')
			elem->next_op = PIPE;
		else if (cmd_str[size] == '&')
		{
			syntax_error();
			return (0);
		}
	}
	elem->next = 0;
	return (elem);
}

int					add_back_cmd_chain_elem(t_cmd_chain **lst
		, char *cmd_str, int parenthesis_depth)
{
	int			i;
	t_cmd_chain	*elem;

	i = 0;
	while (cmd_str[i] && cmd_str[i] != '&' && cmd_str[i] != '|' \
			&& cmd_str[i] != ')')
	{
		if (cmd_str[i] == '\'' || cmd_str[i] == '"')
		{
			i += find_next_index_jump_quotes(cmd_str + i);
			continue ;
		}
		i++;
	}
	if (*lst == 0)
		*lst = ft_create_cmd_chain_elem(cmd_str, parenthesis_depth, i);
	else
	{
		elem = *lst;
		while (elem->next)
			elem = elem->next;
		elem->next = ft_create_cmd_chain_elem(cmd_str
				, parenthesis_depth, i);
	}
	return (i);
}

void				free_t_cmd_chain(t_cmd_chain **lst)
{
	t_cmd_chain	*prev;

	if (*lst == 0)
		return ;
	while ((*lst)->next)
	{
		prev = (*lst);
		*lst = (*lst)->next;
		gc_free(prev->cmd_str);
		gc_free(prev);
	}
	gc_free((*lst)->cmd_str);
	gc_free(*lst);
	*lst = 0;
}

static inline void	check_specific_char(char *cmd_chain
		, int *i, int *parenthesis_depth, t_cmd_chain **lst)
{
	if (ft_alphanum(cmd_chain[*i]) \
			|| cmd_chain[*i] == '.' || cmd_chain[*i] == '/'
			|| cmd_chain[*i] == '>' || cmd_chain[*i] == '<'
			|| cmd_chain[*i] == '"' || cmd_chain[*i] == '\'')
		*i += add_back_cmd_chain_elem(lst
			, cmd_chain + *i, *parenthesis_depth);
	if (cmd_chain[*i] == '(')
		*parenthesis_depth += 1;
	else if (cmd_chain[*i] == ')')
		*parenthesis_depth -= 1;
}

int					parser_cmd_chain(t_data *data, char *cmd_chain)
{
	int			i;
	int			parenthesis_depth;
	t_cmd_chain	*lst;

	i = 0;
	lst = 0;
	parenthesis_depth = 1;
	while (cmd_chain[i])
	{
		while (cmd_chain[i] == ' ')
			i++;
		check_specific_char(cmd_chain, &i, &parenthesis_depth, &lst);
		if (parenthesis_depth < 1)
		{
			syntax_error();
			return (0);
		}
		if (cmd_chain[i])
			i++;
	}
	parser_cmd(data, lst);
	free_t_cmd_chain(&lst);
	return (1);
}
