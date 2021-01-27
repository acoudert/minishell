/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugier <caugier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:15:24 by caugier           #+#    #+#             */
/*   Updated: 2021/01/25 14:15:24 by caugier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

size_t		ft_strlen(const char *str);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memset8(void *s, unsigned long long c, size_t n);
char		*ft_strdup(const char *s);
void		*ft_memcpy8(void *dest, const void *src, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_atoi(const char *nptr);
char		*ft_itoa(int n);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void*));
size_t		ft_strlcat(char *dest, const char *src, size_t size);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *s);
int			ft_alphanum(char c);

#endif
