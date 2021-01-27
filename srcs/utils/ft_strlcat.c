/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:35:06 by acoudert          #+#    #+#             */
/*   Updated: 2021/01/25 15:23:35 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	i;
	size_t	j;

	dest_len = 0;
	while (dest[dest_len] && dest_len < size)
		dest_len++;
	size = size - dest_len;
	if (size == 0)
		return (dest_len + ft_strlen(src));
	i = 0;
	j = 0;
	while (src[i])
	{
		if (size != 1)
		{
			dest[dest_len + j++] = src[i];
			size--;
		}
		i++;
	}
	dest[dest_len + j] = 0;
	return (dest_len + i);
}
