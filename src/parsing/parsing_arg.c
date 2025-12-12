/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 10:34:19 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/11 22:08:55 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../utils/utils.h"

char	**add_arg(char **old_list, int size, char *new_arg)
{
	char	**new_list;
	int		i;

	if (!new_arg)
		return (old_list);
	new_list = malloc(sizeof(char *) * (size + 2));
	if (!new_list)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_list[i] = old_list[i];
		i++;
	}
	new_list[i] = ft_strdup(new_arg);
	new_list[i + 1] = NULL;
	if (size > 0)
		free(old_list);
	return (new_list);
}

static int	word_count(char const *s)
{
	int	i;
	int	count;
	int	is_word;

	i = 0;
	count = 0;
	is_word = 0;
	while (s[i])
	{
		if (s[i] != ' ' && is_word == 0)
		{
			count++;
			is_word = 1;
		}
		else if (s[i] == ' ')
			is_word = 0;
		i++;
	}
	return (count);
}

static char	*set_word(char const *s, int start)
{
	char	*word;
	int		i;
	int		j;
	int		len;

	i = start;
	len = 0;
	while (s[i] && s[i] != ' ')
	{
		len++;
		i++;
	}
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = start;
	j = 0;
	while (s[i] && s[i] != ' ')
		word[j++] = s[i++];
	word[j] = '\0';
	return (word);
}

static char	**gen_array(char **array, char const *s)
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
		if (s[i] != ' ' && !new_word)
		{
			word = set_word(s, i);
			if (!word)
				return (free_array(array), NULL);
			array[level++] = word;
			new_word = 1;
		}
		else if (s[i] == ' ')
			new_word = 0;
		i++;
	}
	array[level] = NULL;
	return (array);
}

char	**split_for_arg(char const *s)
{
	char	**array;
	int		count;

	if (!s)
		return (NULL);
	count = word_count(s);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	return (gen_array(array, s));
}
