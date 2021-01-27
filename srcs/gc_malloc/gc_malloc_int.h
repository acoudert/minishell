/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc_int.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 15:27:10 by caugier           #+#    #+#             */
/*   Updated: 2021/01/15 14:18:24 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_MALLOC_INT_H
# define GC_MALLOC_INT_H

# include "lists.h"
# include "stdlib.h"
# include "minishell.h"

# define BLOCK_COUNT 64

typedef struct	s_callback {
	void	(*func)(void *param);
	void	*param;
}				t_callback;

extern t_gc_list	*g_list_pool;
extern t_gc_list	*g_pointers;
extern t_gc_list	*g_files;
extern t_gc_list	*g_callbacks;
extern t_gc_list	*g_blocks[BLOCK_COUNT];

void			park(t_gc_list *ptr);
t_gc_list		*unpark(void);

#endif
