/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:01:31 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:58:53 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_redir_in_out(char c)
{
	return (c == '<' || c == '>');
}

static char	*extract_redir_token(const char *str, int *i)
{
	int		start;
	char	c;

	if (!is_redir_in_out(str[*i]))
	{
		start = *i;
		while (str[*i] && !is_redir_in_out(str[*i]))
			(*i)++;
		return (ft_substr(str, start, *i - start));
	}
	c = str[*i];
	if (str[*i + 1] == c)
	{
		*i += 2;
		return (ft_substr(str, *i - 2, 2));
	}
	(*i)++;
	return (ft_substr(str, *i - 1, 1));
}

char	**split_redirections(const char *str)
{
	char	**array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	array = malloc(sizeof(char *) * (strlen(str) * 2 + 1));
	if (!array)
		return (NULL);
	while (str[i])
		array[j++] = extract_redir_token(str, &i);
	array[j] = NULL;
	return (array);
}

int	is_error_cmd(t_token *token)
{
	if (!token)
		return (0);
	is_error_redir(token->value);
	return (0);
}

int	is_error_redir(char *str)
{
	char	**array;
	int		i;

	array = split_redirections(str);
	i = 0;
	while (array[i])
	{
		if (ft_strcmp(array[i], "<<") == 0 && array[i + 1]
			&& ft_strcmp(array[i + 1], "<") == 0)
			return (printf("bash: "SYNTAX_ERROR" `newline'\n"), 1);
		else if (ft_isredir(array[i]) && !array[i + 1])
			return (printf("bash: "SYNTAX_ERROR" `newline'\n"), 1);
		else if (ft_isredir(array[i]) && ft_isredir(array[i + 1]))
			return (printf("bash: "SYNTAX_ERROR" `%s'\n", array[i + 1]), 1);
		i++;
	}
	free_array(array);
	return (0);
}
