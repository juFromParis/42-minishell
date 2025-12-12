/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:35:42 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:53:47 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static char	*extract_operator(const char *s, int *i)
{
	char	*op;

	if (s[*i + 1] == s[*i])
	{
		op = ft_strncpy(s, *i, 2);
		*i += 2;
	}
	else
	{
		op = ft_strncpy(s, *i, 1);
		*i += 1;
	}
	return (op);
}

static char	*extract_word(const char *s, int *i)
{
	int	start;

	start = *i;
	while (s[*i] && !ft_isspace(s[*i]) && !is_operator_char(s[*i]))
		(*i)++;
	return (ft_strncpy(s, start, *i - start));
}

char	**split_for_redir(const char *s)
{
	char	**array;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	array = malloc(sizeof(char *) * (count_tokens(s) + 1));
	if (!array)
		return (NULL);
	while (s[i])
	{
		if (ft_isspace(s[i]))
		{
			i++;
			continue ;
		}
		if (is_operator_char(s[i]))
			array[k++] = extract_operator(s, &i);
		else
			array[k++] = extract_word(s, &i);
	}
	array[k] = NULL;
	return (array);
}
