/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:03:39 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/12 21:27:20 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stddef.h>
# include <stdlib.h>

// size_t	ft_strlen(const char *str);
// char	*ft_strdup(const char *s1);
// size_t	ft_strlcpy(char *dest, const char *src, size_t size);
// char	*ft_strjoin(char const *s1, char const *s2);
// char	*ft_strchr(const char *s, int c);
// char	**ft_split(const char *s, char c);
size_t	ft_strcpy(char *dest, char *src);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_revstrncmp(const char *s1, const char *s2, size_t n);
// char	*ft_strjoin(char const *s1, char const *s2);
// char	*ft_strnstr(const char *big, const char *little, size_t len);
// int		ft_isalpha(int a);
// int		ft_isdigit(int c);
// int		ft_isalnum(int c);
#endif