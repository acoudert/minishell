/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:14:15 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 23:02:06 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

typedef struct			s_gc_list {
	void				*content;
	struct s_gc_list	*next;
}						t_gc_list;

t_gc_list				*list_pop(t_gc_list **list);
void					list_push_front(t_gc_list **list, t_gc_list *elem);

#endif
