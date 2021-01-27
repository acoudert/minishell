/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:51:17 by caugier           #+#    #+#             */
/*   Updated: 2021/01/26 15:00:16 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_vars(void)
{
	int			val;
	const char	*str;

	str = get_env("SHLVL");
	if (str == NULL)
		val = 0;
	else
		val = ft_atoi(str);
	val++;
	set_env("SHLVL", ft_itoa(val));
}
