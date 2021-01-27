/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:58:22 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 23:58:22 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_MALLOC_H
# define GC_MALLOC_H

void		gc_free(void *ptr);
void		*gc_malloc(size_t n) __attribute__((alloc_size(1)));
int			gc_open(const char *path, int mode);
void		gc_close(int fd);
void		gc_add_cb(void (*cb)(void *), void *param);
void		gc_rm_cb(void (*cb)(void *), void *param);
void		*gc_exit(int n) __attribute__((noreturn));

#endif
