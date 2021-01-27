/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 16:45:21 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"

t_list_bis	*ft_fd_in_lst(int fd, t_list_bis **file_lst)
{
	t_list_bis		*curr;

	if (*file_lst == 0)
		if (!(*file_lst = ft_lstnew(fd)))
			return (0);
	curr = *file_lst;
	while (curr)
	{
		if (curr->fd == fd)
			return (curr);
		else if (curr->next == 0)
			if (!(curr->next = ft_lstnew(fd)))
				return (0);
		curr = curr->next;
	}
	return (0);
}

int			ft_read_line(int fd, t_list_bis *curr)
{
	int		bytes;
	char	buffer[2];
	char	*str_to_free;

	while (ft_strchr(curr->str, '\n') == 0)
	{
		if ((bytes = read(fd, buffer, 1)) == ERROR)
			return (ERROR);
		buffer[bytes] = 0;
		str_to_free = curr->str;
		if (!(curr->str = ft_strjoin(curr->str, buffer)))
			return (ERROR);
		gc_free(str_to_free);
		if (bytes < 1)
			break ;
	}
	return (1);
}

int			ft_create_line(char **line, t_list_bis *curr)
{
	int		i;
	char	*buffer;
	int		ret_val;

	i = 0;
	while (curr->str[i] && curr->str[i] != '\n')
		i++;
	ret_val = (curr->str[i] == '\n') ? READ_LINE : END_FILE;
	if (!(*line = (char*)gc_malloc(sizeof(char) * (i + 1))))
		return (0);
	buffer = curr->str;
	curr->str = (curr->str[i] == '\n') ? curr->str + i + 1 : curr->str + i;
	if (!(curr->str = ft_strdup(curr->str)))
		return (ERROR);
	(*line)[i] = 0;
	while (--i >= 0)
		(*line)[i] = buffer[i];
	gc_free(buffer);
	return (ret_val);
}

void		ft_free_lst(int fd, t_list_bis **file_lst)
{
	t_list_bis		*curr;
	t_list_bis		*next;

	curr = *file_lst;
	if (!curr)
		return ;
	if (curr->fd == fd)
	{
		*file_lst = (*file_lst)->next;
		(curr->str) ? gc_free(curr->str) : 0;
		gc_free(curr);
		return ;
	}
	while (curr && curr->next)
	{
		next = curr->next->next;
		if (curr->next->fd == fd)
		{
			(curr->next->str) ? gc_free(curr->next->str) : 0;
			gc_free(curr->next);
			curr->next = next;
		}
		curr = curr->next;
	}
}

int			get_next_line(int fd, char **line)
{
	static t_list_bis		*file_lst = 0;
	t_list_bis				*curr;
	int						ret_val;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (ERROR);
	if (!(curr = ft_fd_in_lst(fd, &file_lst)))
	{
		ft_free_lst(fd, &file_lst);
		return (ERROR);
	}
	if (ft_read_line(fd, curr) == ERROR)
	{
		ft_free_lst(fd, &file_lst);
		return (ERROR);
	}
	ret_val = ft_create_line(line, curr);
	if (ret_val == ERROR || ret_val == END_FILE)
		ft_free_lst(fd, &file_lst);
	return (ret_val);
}
