/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_chains.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:30:00 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 10:30:01 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_update_cmd_chains_var(char *cmd_chains
		, char *cmd_found_bool, int *nb)
{
	int	i;

	i = 1;
	if (ft_alphanum(*cmd_chains))
		*cmd_found_bool = 1;
	if (*cmd_chains == ';' && *cmd_found_bool == 0)
		return (-1);
	else if (*cmd_chains == ';' \
		|| (*(cmd_chains + 1) == 0 && *cmd_found_bool == 1))
	{
		*cmd_found_bool = 0;
		(*nb)++;
	}
	else if (ft_alphanum(*cmd_chains) || \
			*cmd_chains == '\'' || *cmd_chains == '"')
	{
		*cmd_found_bool = 1;
		if (*cmd_chains == '\'' || *cmd_chains == '"')
			i = find_next_index_jump_quotes(cmd_chains + i);
	}
	return (i);
}

static inline int	ft_calc_nb_cmd_chains(char *cmd_chains)
{
	int		nb;
	int		i;
	int		incr_i_val;
	char	cmd_found_bool;

	nb = 0;
	i = 0;
	cmd_found_bool = 0;
	while (cmd_chains[i] == ' ')
		i++;
	while (cmd_chains[i])
	{
		incr_i_val = ft_update_cmd_chains_var(cmd_chains + i
			, &cmd_found_bool, &nb);
		if (incr_i_val == -1)
			return (-1);
		i += incr_i_val;
	}
	return (nb);
}

int					ft_next_cmd_chain_index(char *cmd_chains)
{
	int	i;

	i = 0;
	while (cmd_chains[i])
	{
		if (cmd_chains[i] == '\'' || cmd_chains[i] == '"')
		{
			i += find_next_index_jump_quotes(cmd_chains + i);
			continue ;
		}
		else if (cmd_chains[i] == ';')
			break ;
		i++;
	}
	if (cmd_chains[i] == ';')
		return (i + 1);
	return (i);
}

char				*ft_create_cmd_chain(char *cmd_chains)
{
	int		i;
	int		size;
	char	*cmd_chain;

	size = ft_next_cmd_chain_index(cmd_chains);
	if (cmd_chains[size - 1] == ';')
		size--;
	if (!(cmd_chain = (char*)gc_malloc(sizeof(char) * (size + 1))))
		return (0);
	i = 0;
	while (i < size)
	{
		cmd_chain[i] = cmd_chains[i];
		i++;
	}
	cmd_chain[i] = 0;
	return (cmd_chain);
}

void				parser_cmd_chains(t_data *data, char *cmd_chains)
{
	int		nb_cmd_chains;
	char	*cmd_chain;
	int		i;

	nb_cmd_chains = ft_calc_nb_cmd_chains(cmd_chains);
	if (nb_cmd_chains == -1)
	{
		syntax_error();
		return ;
	}
	i = 0;
	while (nb_cmd_chains > 0)
	{
		if (!(cmd_chain = ft_create_cmd_chain(cmd_chains + i)))
			return ;
		if (!(parser_cmd_chain(data, cmd_chain)))
			return ;
		i += ft_next_cmd_chain_index(cmd_chains + i);
		core_run(data);
		free_parser(data);
		nb_cmd_chains--;
		gc_free(cmd_chain);
	}
}
