/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_double_quote_str.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:30:14 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 23:30:51 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_quote_str_old(char *str, int i)
{
	char	*ret_str;
	int		k;

	k = ft_next_quote(str + i);
	if (!(ret_str = (char*)gc_malloc(sizeof(char) * (k - 1))))
		return (0);
	*ret_str = 0;
	ft_strlcat(ret_str, str + i + 1, k);
	return (ret_str);
}

static char	*apply_escape_seq(char *str, int i)
{
	str[i] = str[i + 1];
	i++;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	return (str);
}

static char	*get_quote_str_new(char *old, int ret_code)
{
	int		i;
	char	*new;

	if (!(new = (char*)gc_malloc(sizeof(char) * (ft_strlen(old) + 1))))
		return (0);
	*new = 0;
	ft_strlcat(new, old, ft_strlen(old) + 1);
	i = 0;
	while (new[i])
	{
		new = check_var(new, i, ret_code);
		if (new[i] == '\\')
			new = apply_escape_seq(new, i);
		if (!new)
			return (0);
		i++;
	}
	return (new);
}

static char	*get_quote_ret_str(char *str, char *old, char *new, int i)
{
	char	*ret_str;
	int		size;

	size = ft_strlen(str) + ft_strlen(new) - ft_strlen(old) - 1;
	if (!(ret_str = (char*)gc_malloc(sizeof(char) * size)))
		return (0);
	*ret_str = 0;
	ft_strlcat(ret_str, str, i + 1);
	ft_strlcat(ret_str, new, size);
	ft_strlcat(ret_str, str + i + ft_strlen(old) + 2, size);
	return (ret_str);
}

char		*update_double_quote_str(char *str, int *i, int ret_code)
{
	char	*ret_str;
	char	*quote_str_old;
	char	*quote_str_new;

	if (!(quote_str_old = get_quote_str_old(str, *i)))
		return (0);
	if (!(quote_str_new = get_quote_str_new(quote_str_old, ret_code)))
		return (0);
	if (!(ret_str =
		get_quote_ret_str(str, quote_str_old, quote_str_new, *i)))
		return (0);
	*i = *i + ft_strlen(quote_str_new) - 1;
	gc_free(quote_str_old);
	gc_free(quote_str_new);
	return (ret_str);
}
