/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 17:07:42 by caugier           #+#    #+#             */
/*   Updated: 2021/01/16 12:26:34 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "minishell.h"

# define EC_SUCCESS 0
# define EC_UNK 1
# define EC_TMPTR 2
# define EC_ILLF 3
# define EC_NOMEM 4
# define EC_CNTCLOSE 5
# define EC_CNTOPEN 6
# define EC_ILCBRM 7
# define EC_TMARGS 8
# define EC_HOMEUNST 9
# define EC_NARGR 10
# define EC_GCWD 11
# define EC_NVID 12

const char	*ft_strerror(int error);
void		put_err_header(void);
void		builtin_error(t_builtin builtin, int error);
void		builtin_errno(t_builtin builtin);
void		put_err(int error);
void		put_strerrno(void);
void		fatal(int error);
void		fatal_errno(void);
void		suf_err(int error, const char *suf);
void		suf_strerrno(const char *suf);
void		syntax_error(void);

#endif
