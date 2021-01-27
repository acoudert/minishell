/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:35:14 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 14:42:51 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline t_status	ft_init_status(void)
{
	t_status	status;

	status.depth = 0;
	status.s_quote = 0;
	status.d_quote = 0;
	return (status);
}

static inline int		status_operator(t_char *cmd, int i)
{
	int	j;

	j = i;
	if (cmd[j].key == '&' && cmd[j + 1].key != '&')
		return (-1);
	else if (cmd[j].key == cmd[j + 1].key)
		j++;
	j++;
	while (cmd[j].key && (cmd[j].key == ' ' || cmd[j].key == '\n'))
		j++;
	if (cmd[j].key == 0)
		return (-1);
	return (j - i - 1);
}

static inline int		skip_quote(t_char *cmd, t_status *status
		, int *i, char c)
{
	if (c == '\'' && status->s_quote == 0)
		status->s_quote += 1;
	else if (c == '\'')
		status->s_quote -= 1;
	else if (c == '"' && status->d_quote == 0)
		status->d_quote += 1;
	else
		status->d_quote -= 1;
	*i += find_next_cmd_tab_quote(cmd + *i) - 1;
	if (!cmd[*i].key)
		return (0);
	return (1);
}

static inline int		update_status(t_char *cmd, t_status *status, int *i)
{
	int	j;

	if (cmd[*i].key == '(')
	{
		status->depth += 1;
	}
	else if (cmd[*i].key == ')')
	{
		status->depth -= 1;
		if (status->depth < 0)
			return (0);
	}
	else if (cmd[*i].key == '&' || cmd[*i].key == '|'
			|| cmd[*i].key == '>' || cmd[*i].key == '<')
	{
		j = status_operator(cmd, *i);
		if (j == -1)
			return (0);
		*i += j;
	}
	return (1);
}

char					cmd_end(t_char *cmd, char *buf)
{
	int			i;
	t_status	status;

	if (cmd == 0 || buf[0] != '\n')
		return (0);
	i = -1;
	status = ft_init_status();
	while (cmd[++i].key)
	{
		if (cmd[i].key == '\\')
			i++;
		else if ((cmd[i].key == '\'' || cmd[i].key == '"'))
		{
			if (!skip_quote(cmd, &status, &i, cmd[i].key))
				return (0);
		}
		else if ((cmd[i].key == '(' || cmd[i].key == ')' || cmd[i].key == '&'
				|| cmd[i].key == '|' || cmd[i].key == '>' || cmd[i].key == '<')
				&& !update_status(cmd, &status, &i))
			return (0);
	}
	if (cmd[i].key == 0 && buf[0] == '\n' && status.depth == 0
			&& status.s_quote == 0 && status.d_quote == 0)
		return (1);
	return (0);
}
