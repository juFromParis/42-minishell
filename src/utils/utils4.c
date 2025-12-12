/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:46:19 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/12 21:16:28 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../inc/minishell.h"

// size_t	ft_strlcpy(char *dest, const char *src, size_t size)
// {
// 	char	*d;
// 	size_t	src_len;
// 	size_t	i;

// 	i = 0;
// 	d = dest;
// 	src_len = ft_strlen(src);
// 	if (src == NULL || dest == NULL)
// 		return (0);
// 	if (size == 0)
// 		return (src_len);
// 	while ((i < size - 1) && src[i])
// 	{
// 		d[i] = src[i];
// 		i++;
// 	}
// 	if (size > i)
// 		d[i] = '\0';
// 	return (src_len);
// }

// char	*ft_strdup(const char *s1)
// {
// 	char *str;
// 	size_t len;

// 	len = ft_strlen(s1) + 1;
// 	str = (char *)malloc(len);
// 	if (!str)
// 		return (NULL);
// 	ft_strlcpy(str, s1, len);
// 	return (str);
// }

int	ft_isalpha(int a)
{
	if (('a' <= a && a <= 'z') || ('A' <= a && a <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (('0' <= c && c <= '9'))
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	else
		return (0);
}