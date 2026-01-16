/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:58:27 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/15 16:45:15 by jderachi         ###   ########.fr       */
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

int	is_error_redir(char *str)
{
	char	**a;
	int		i;

	a = split_redirections(str);
	i = 0;
	while (a[i])
	{
		if (!ft_strcmp(a[i], "<") && a[i + 1] && !ft_strcmp(a[i + 1], ">"))
			return (return_error("newline", a));
		if (!ft_strcmp(a[i], "<<") && a[i + 1] && !ft_strcmp(a[i + 1], "<"))
			return (return_error("newline", a));
		else if (ft_isredir(a[i]) && !a[i + 1])
			return (return_error("newline", a));
		else if (ft_isredir(a[i]) && a[i + 1] && !ft_strcmp(a[i + 1], " ")
			&& a[i + 2] && ft_isredir(a[i + 2]))
			return (return_error(a[i + 2], a));
		else if (ft_isredir(a[i]) && a[i + 1] && ft_isredir(a[i + 1]))
			return (return_error(a[i + 1], a));
		else if (ft_isredir(a[i]) && a[i + 1] && !ft_strcmp(a[i + 1], " "))
			return (return_error(a[i], a));
		i++;
	}
	free_array(a);
	return (0);
}


