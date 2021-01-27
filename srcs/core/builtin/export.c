/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:28:39 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "minishell.h"

static int		validate_name(const char *str)
{
	if (*str >= '0' && *str < '9')
		return (0);
	while (*str != '=' && *str != '\0')
	{
		if (!((*str >= '0' && *str <= '9') || (*str >= 'a' && *str <= 'z')
			|| (*str >= 'A' && *str <= 'Z') || *str == '_'))
			return (0);
		str++;
	}
	return (1);
}

static size_t	arg_name_len(const char *str)
{
	const char	*s;

	s = str;
	while (*str != '\0' && *str != '=')
		str++;
	return (str - s);
}

static void		no_arg(int stdout_fd)
{
	const char	**envp;
	size_t		len;

	envp = (const char **)env();
	while (*envp != NULL)
	{
		write(stdout_fd, "declare -x ", 11);
		len = arg_name_len(*envp);
		write(stdout_fd, *envp, len);
		if ((*envp)[len] == '=')
		{
			write(stdout_fd, "=\"", 2);
			write(stdout_fd, &(*envp)[len + 1], ft_strlen(&(*envp)[len + 1]));
			write(stdout_fd, "\"\n", 2);
		}
		else
			write(stdout_fd, "\n", 1);
		envp++;
	}
}

static int		for_each(char *arg)
{
	char	*str;

	if (validate_name(arg) == 0)
	{
		put_err_header();
		write(STDERR_FILENO, "export : `", 10);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, "': ", 3);
		str = (char *)ft_strerror(EC_NVID);
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, "\n", 1);
		return (1);
	}
	str = arg;
	while (*str != '\0' && *str != '=')
		str++;
	if (*str == '=')
	{
		*str = '\0';
		str++;
	}
	set_env(arg, str);
	return (0);
}

void			ft_export(t_data *data, int stdout_fd)
{
	size_t	i;

	data->ret_code = 0;
	i = 1;
	if (data->cmd->argv[i] == NULL)
	{
		no_arg(stdout_fd);
		return ;
	}
	while (data->cmd->argv[i] != NULL)
	{
		data->ret_code |= for_each(data->cmd->argv[i]);
		i++;
	}
}
