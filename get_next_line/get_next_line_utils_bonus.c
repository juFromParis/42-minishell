/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:03:00 by vtaniga           #+#    #+#             */
/*   Updated: 2025/07/19 18:15:41 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	handle_newline(char *buffer, int index, char **quinon)
{
	if (buffer[index] == '\n')
	{
		if (buffer[index + 1])
		{
			*quinon = ft_strdup(buffer + index + 1);
			if (!*quinon)
				return (0);
		}
		return (2);
	}
	return (1);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s1) + 1;
	str = (char *)malloc(len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len);
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	char	*d;
	size_t	src_len;
	size_t	i;

	i = 0;
	d = dest;
	src_len = ft_strlen(src);
	if (src == NULL || dest == NULL)
		return (0);
	if (size == 0)
		return (src_len);
	while ((i < size - 1) && src[i])
	{
		d[i] = src[i];
		i++;
	}
	if (size > i)
		d[i] = '\0';
	return (src_len);
}

size_t	ft_strlen(const char *str)
{
	int	index;

	if (!str)
		return (0);
	index = 0;
	while (str[index])
	{
		index++;
	}
	return (index);
}
