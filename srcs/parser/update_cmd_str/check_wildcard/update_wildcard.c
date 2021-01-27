/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:13:05 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_wildcard	*update_t_wildcard(t_wildcard **wc, struct dirent *s)
{
	t_wildcard	*new;

	if (match(s->d_name, (*wc)->patterns->content))
	{
		new = gc_malloc(sizeof(*new));
		new->patterns = (*wc)->patterns->next;
		new->cwd = path_join((*wc)->cwd, s->d_name);
		new->string = path_join((*wc)->string, s->d_name);
		new->next = NULL;
		ft_wc_addback(wc, new);
		expand_wc(new);
	}
	return (*wc);
}

void		expand_wc(t_wildcard *wc)
{
	DIR				*d;
	struct dirent	*s;

	if (wc->patterns == NULL)
		return ;
	d = opendir(wc->cwd);
	if (d == NULL)
		return ;
	gc_add_cb((void *)closedir, d);
	s = readdir(d);
	while (s != NULL)
	{
		if (s->d_name[0] != '.' || ((char *)wc->patterns->content)[0] == '.')
			wc = update_t_wildcard(&wc, s);
		s = readdir(d);
	}
	closedir(d);
	gc_rm_cb((void *)closedir, d);
}

char		*quote_wc(char *str)
{
	size_t	len;
	char	*beg;

	beg = str;
	while (*str != ' ' && *str != '\0')
		str++;
	len = str - beg;
	str = gc_malloc(len + 3);
	str[0] = '"';
	str[len + 1] = '"';
	str[len + 2] = '\0';
	ft_memcpy(&str[1], beg, len);
	return (str);
}

void		fill_wc(char *str, t_wildcard *wc)
{
	wc->patterns = get_patterns(str);
	wc->next = NULL;
	if (*str != '/')
	{
		wc->string = getcwd(NULL, 0);
		gc_add_cb(free, wc->string);
		wc->cwd = ft_strdup(wc->string);
		gc_rm_cb(free, wc->string);
		free(wc->string);
		wc->string = ft_strdup("");
	}
	else
	{
		wc->cwd = ft_strdup("/");
		wc->string = ft_strdup("/");
	}
}
