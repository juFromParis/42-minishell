/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 10:34:19 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/15 13:02:31 by jderachi         ###   ########.fr       */
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
size_t	split_len(char **split)
{
	size_t	len;
	if(!split)
		return (0);
	len = 0;
	while (split[len])
		len++;
	return (len);
}

char	**insert_arg(char **old_list, size_t wild_index, char **new_args)
{
	char	**new_list;
	size_t	i;
	size_t	size;
	size_t	new_size;
	size_t	j;

	size = split_len(old_list);
	if (!new_args || wild_index < 0 || wild_index >= size)
		return (old_list);
	new_size = split_len(new_args);
	new_list = malloc(sizeof(char *) * (size + new_size));
	if (!new_list)
		return (NULL);
	i = 0;
	while (i < wild_index)
	{
		new_list[i] = old_list[i];
		i++;
	}
	j = 0;
	while (j < new_size)
	{
		new_list[i + j] = ft_strdup(new_args[j]);
		j++;
	}
	i += new_size;
	while (wild_index + 1 < size)
	{
		new_list[i] = old_list[wild_index + 1];
		wild_index++;
		i++;
	}
	new_list[i] = NULL;
	if (size > 0)
		free(old_list);
	return (new_list);
}

int	*add_int(int *old_list, int size, int new_val)
{
	int	*new_list;
	int	i;

	new_list = malloc(sizeof(int) * (size + 2));
	if (!new_list)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_list[i] = old_list[i];
		i++;
	}
	new_list[i] = new_val;
	new_list[i + 1] = -1;
	if (size > 0)
		free(old_list);
	return (new_list);
}

static int	is_ws(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

static int	extract_one_arg(const char *s, int i, char *buffer)
{
	int		k;
	char	quote;

	k = 0;
	quote = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			if (quote == 0)
				quote = s[i];
			else if (quote == s[i])
				quote = 0;
			buffer[k++] = s[i++];
			continue ;
		}
		if (is_ws(s[i]) && quote == 0)
			break ;
		buffer[k++] = s[i++];
	}
	buffer[k] = '\0';
	return (i);
}

char	**split_for_arg(const char *s)
{
	char	**args;
	char	buffer[4096];
	int		i;
	int		j;

	args = malloc(sizeof(char *) * (ft_strlen(s) + 1));
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && is_ws(s[i]))
			i++;
		if (!s[i])
			break ;
		i = extract_one_arg(s, i, buffer);
		args[j++] = ft_strdup(buffer);
	}
	args[j] = NULL;
	return (args);
}

