/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:35:42 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/05 12:53:22 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	is_operator_char(char c)
{
	return (c == '<' || c == '>');
}

int	count_tokens(const char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (isspace(s[i]))
			i++;
		else if (is_operator_char(s[i]))
		{
			count++;
			if (s[i + 1] == s[i])
				i += 2;
			else
				i++;
		}
		else
		{
			count++;
			while (s[i] && !isspace(s[i]) && !is_operator_char(s[i]))
				i++;
		}
	}
	return (count);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}


char	*ft_strcpy(const char *s, int start, int len)
{
	char	*dest;

	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s + start, len);
	dest[len] = '\0';
	return (dest);
}

char **cmd_split(const char *s)
{
	char	**array;
	int		i;
	int		k;
	int		token_count;
	int		start;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	token_count = count_tokens(s);
	array = malloc(sizeof(char *) * (token_count + 1));
	if (!array)
		return (NULL);
	while (s[i])
	{
		if (ft_isspace(s[i]))
			i++;
		else if (is_operator_char(s[i]))
		{
			if (s[i + 1] == s[i])
			{
				array[k++] = ft_strcpy(s, i, 2);
				i += 2;
			}
			else
			{
				array[k++] = ft_strcpy(s, i, 1);
				i++;
			}
		}
		else
		{
			start = i;
			while (s[i] && !isspace(s[i]) && !is_operator_char(s[i]))
				i++;
			array[k++] = ft_strcpy(s, start, i - start);
		}
	}
	array[k] = NULL;
	return (array);
}
