/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:28:56 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "minishell.h"

static int	validate_name(const char *str)
{
	if (*str >= '0' && *str < '9')
		return (0);
	while (*str != '\0')
	{
		if (!((*str >= '0' && *str <= '9') || (*str >= 'a' && *str <= 'z')
			|| (*str >= 'A' && *str <= 'Z') || *str == '_'))
			return (0);
		str++;
	}
	return (1);
}

static int	for_each(char *arg)
{
	char	*str;

	if (validate_name(arg) == 0)
	{
		put_err_header();
		write(STDERR_FILENO, "unset : `", 9);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, "': ", 3);
		str = (char *)ft_strerror(EC_NVID);
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, "\n", 1);
		return (1);
	}
	del_env(arg);
	return (0);
}

void		ft_unset(t_data *data, int stdout_fd)
{
	size_t	i;

	(void)stdout_fd;
	data->ret_code = 0;
	i = 1;
	while (data->cmd->argv[i] != NULL)
	{
		data->ret_code |= for_each(data->cmd->argv[i]);
		i++;
	}
}
