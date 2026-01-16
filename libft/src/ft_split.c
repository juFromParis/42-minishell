/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:30:18 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:31:45 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	free_malloc(char **array, int level)
{
	while (level > 0)
		free(array[--level]);
	free(array);
}

int	word_count(char const *s, char c)
{
	int	i;
	int	count;
	int	is_word;

	i = 0;
	count = 0;
	is_word = 0;
	while (s[i])
	{
		if (s[i] != c && is_word == 0)
		{
			count++;
			is_word = 1;
		}
		else if (s[i] == c)
			is_word = 0;
		i++;
	}
	return (count);
}

char	*set_word(char const *s, int start, char c)
{
	char	*word;
	int		i;
	int		j;
	int		len;

	i = start;
	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = start;
	j = 0;
	while (s[i] && s[i] != c)
		word[j++] = s[i++];
	word[j] = '\0';
	return (word);
}

char	**gen_array(char **array, char const *s, char c)
{
	int		i;
	int		level;
	int		new_word;
	char	*word;

	i = 0;
	level = 0;
	new_word = 0;
	while (s[i])
	{
		if (s[i] != c && !new_word)
		{
			word = set_word(s, i, c);
			if (!word)
				return (free_malloc(array, level), NULL);
			array[level++] = word;
			new_word = 1;
		}
		else if (s[i] == c)
			new_word = 0;
		i++;
	}
	array[level] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		count;

	if (!s)
		return (NULL);
	count = word_count(s, c);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	return (gen_array(array, s, c));
}

/*
int	main(void)
{
	char **result = ft_split("  Hello  world this is 42  ", ' ');
	int i = 0;
	
	while (result[i])
	{
		printf("Word %d: %s\n", i, result[i]);
		free(result[i]);
		i++;
	}
	free(result);
	return 0;
}
*/
