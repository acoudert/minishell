/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hostname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:35:44 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:35:44 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_hostname(int fd)
{
	char	*hostname;
	char	*temp;
	char	buf[2];

	if (!(hostname = (char*)gc_malloc(sizeof(char))))
		return (0);
	*hostname = 0;
	while (read(fd, buf, 1))
	{
		buf[1] = 0;
		temp = hostname;
		if (!(hostname = (char*)gc_malloc(sizeof(char) *
				(ft_strlen(temp) + 2))))
			return (0);
		*hostname = 0;
		ft_strlcat(hostname, temp, ft_strlen(temp) + 1);
		gc_free(temp);
		if (buf[0] == '\n')
			break ;
		ft_strlcat(hostname, buf, ft_strlen(hostname) + 2);
	}
	return (hostname);
}

char	*get_hostname(void)
{
	int		fds[2];
	int		pid;
	char	*argv[2];
	char	*hostname;

	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		argv[0] = "/bin/hostname";
		argv[1] = 0;
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		execve(argv[0], argv, env());
		gc_exit(-1);
	}
	waitpid(pid, &pid, 0);
	if (WEXITSTATUS(pid) != 0)
		return (ft_strdup("bashathlon"));
	close(fds[1]);
	if (!(hostname = read_hostname(fds[0])))
		return (0);
	close(fds[0]);
	return (hostname);
}
