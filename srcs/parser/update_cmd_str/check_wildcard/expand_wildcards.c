/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:41:51 by caugier           #+#    #+#             */
/*   Updated: 2021/01/26 19:41:54 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	measure_wc_str(t_wildcard *wc, t_wildcard **c, size_t *len)
{
	(*len) = 0;
	(*c) = wc;
	while (wc != NULL)
	{
		if (wc->patterns == NULL)
			(*len) += ft_strlen(wc->string) + 1;
		wc = wc->next;
	}
}

char	*get_ret_val(t_wildcard *wc, t_wildcard *c, size_t len)
{
	char	*ret;
	size_t	l;
	void	*ptr;

	ptr = c->patterns;
	ret = gc_malloc(len + 2);
	while (c != NULL)
	{
		if (c->patterns == NULL)
		{
			l = ft_strlen(c->string);
			ft_memcpy(ret, c->string, l);
			ret[l] = ' ';
			ret += l + 1;
		}
		gc_free(c->cwd);
		gc_free(c->string);
		wc = c;
		c = c->next;
		gc_free(wc);
	}
	*ret = '\0';
	ft_lstclear((t_list **)&ptr, gc_free);
	return (ret - len);
}

char	*expand_wildcards(char *str)
{
	t_wildcard	*wc;
	t_wildcard	*c;
	size_t		len;

	wc = gc_malloc(sizeof(*wc));
	fill_wc(str, wc);
	if (wc->cwd == NULL)
		return (quote_wc(str));
	expand_wc(wc);
	measure_wc_str(wc, &c, &len);
	if (len == 0)
		return (quote_wc(str));
	return (get_ret_val(wc, c, len));
}
