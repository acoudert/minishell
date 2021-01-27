/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:28:49 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:28:49 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_builtin(char *str)
{
	if (ft_strcmp(str, "cd") == 0)
		return (CD);
	else if (ft_strcmp(str, "export") == 0)
		return (EXPORT);
	else if (ft_strcmp(str, "unset") == 0)
		return (UNSET);
	else if (ft_strcmp(str, "exit") == 0)
		return (EXIT);
	return (NONE);
}
