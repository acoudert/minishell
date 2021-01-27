/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:36:05 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/26 11:55:17 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(void)
{
	write(2, RED, ft_strlen(RED));
	write(2, "minishell: Syntax error\n", 24);
	write(2, NC, ft_strlen(NC));
}
