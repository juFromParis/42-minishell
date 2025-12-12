/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:56:40 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/04 12:06:21 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
static size_t	count_words(const char *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
		{
			in_word = 0;
		}
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static void	free_all(char **arr, size_t n)
{
	while (n--)
		free(arr[n]);
	free(arr);
}

static char	*word_dup(const char *start, size_t len)
{
	char	*word;
	size_t	i;

	i = 0;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
		word[len] = '\0';
	return (word);
}

static char	**array_dup(char **result, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			result[j] = word_dup(s + start, i - start);
			if (!result[j++])
			{
				free_all(result, j - 1);
				return (NULL);
			}
		}
	}
	result[j] = NULL;
	return (result);
}

char	**ft_split(const char *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	if (!array_dup(result, s, c))
		return (NULL);
	return (result);
}
