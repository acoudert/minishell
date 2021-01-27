/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:57:28 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 23:52:21 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <term.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>

# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define BLUE	"\033[1;34m"
# define NC		"\033[0m"
# define LEFT   "\033[1D"
# define RIGHT  "\033[1C"
# define TOP    "\033[1A"
# define BOT    "\033[1B"

# include "struct.h"
# include "utils.h"
# include "errors.h"
# include "gc_malloc.h"
# include "env.h"
# include "input.h"
# include "parser.h"
# include "builtin.h"
# include "core.h"

#endif
