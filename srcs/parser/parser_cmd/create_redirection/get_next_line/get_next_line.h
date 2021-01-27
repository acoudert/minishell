/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:41:53 by acoudert          #+#    #+#             */
/*   Updated: 2020/11/21 15:28:25 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	32
# endif

# include <unistd.h>
# include <stdlib.h>
# include "minishell.h"

enum					e_ret_val
{
	READ_LINE = 1,
	END_FILE = 0,
	ERROR = -1
};

typedef struct			s_list_bis
{
	struct s_list_bis	*next;
	char				*str;
	int					fd;
}						t_list_bis;

int						get_next_line(int fd, char **line);

t_list_bis				*ft_fd_in_lst(int fd, t_list_bis **file_lst);
int						ft_read_line(int fd, t_list_bis *curr);
int						ft_create_line(char **line, t_list_bis *curr);
void					ft_free_lst(int fd, t_list_bis **file_lst);

t_list_bis				*ft_lstnew(int fd);
char					*ft_strchr(char *s, int c);

#endif
