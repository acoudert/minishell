/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_empty_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:30:12 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:30:12 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_remove_empty_quotes(char *str)
{
	int	i;
	int	loop_nb;

	loop_nb = 2;
	while (loop_nb > 0)
	{
		i = 0;
		while (str[i])
		{
			str[i] = str[i + 1];
			i++;
		}
		str[i] = 0;
		loop_nb--;
	}
}
