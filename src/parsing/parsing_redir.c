/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:35:42 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/13 11:58:31 by jderachi         ###   ########.fr       */
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

char	**split_for_redir(const char *s)
{
	char	**args;
	char	buffer[4096];
	int		i;
	int		j;
	int		k;
	char	quote;

	args = malloc(sizeof(char *) * (ft_strlen(s) + 2));
	if (!args)
		return (NULL);

	i = 0;
	j = 0;
	k = 0;
	quote = 0;

	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			if (!quote)
				quote = s[i];
			else if (quote == s[i])
				quote = 0;
			buffer[k++] = s[i++];
			continue ;
		}
		if (!quote && s[i] == ' ')
		{
			if (k > 0)
			{
				buffer[k] = '\0';
				args[j++] = ft_strdup(buffer);
				k = 0;
			}
			i++;
			continue ;
		}
		if (!quote && is_operator_char(s[i]))
		{
			if (k > 0)
			{
				buffer[k] = '\0';
				args[j++] = ft_strdup(buffer);
				k = 0;
			}
			if (s[i + 1] == s[i])
			{
				buffer[0] = s[i];
				buffer[1] = s[i];
				buffer[2] = '\0';
				args[j++] = ft_strdup(buffer);
				i += 2;
			}
			else
			{
				buffer[0] = s[i];
				buffer[1] = '\0';
				args[j++] = ft_strdup(buffer);
				i++;
			}
			continue ;
		}
		buffer[k++] = s[i++];
		if (k >= 4095)
			break ;
	}

	if (k > 0)
	{
		buffer[k] = '\0';
		args[j++] = ft_strdup(buffer);
	}
	args[j] = NULL;
	return (args);
}
