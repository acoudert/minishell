/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:35:10 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:35:10 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tty_raw_setup(void)
{
	struct termios info;

	tcgetattr(0, &info);
	info.c_lflag &= ~(ICANON | ECHO);
	info.c_cc[VMIN] = 1;
	info.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &info);
}

void	tty_default_setup(void)
{
	struct termios info;

	tcgetattr(0, &info);
	info.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSANOW, &info);
	write(1, "\n", 1);
}
