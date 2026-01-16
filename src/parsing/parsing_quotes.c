/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:48:10 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/09 14:55:27 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../utils/utils.h"

int	quote_type(const char *s)
{
	int	i;
	int	j;

	if (!s)
		return (0);
	i = 0;
	j = (int)ft_strlen(s) - 1;
	while (s[i] == ' ')
		i++;
	while (j > i && s[j] == ' ')
		j--;
	if (j - i + 1 >= 2 && s[i] == '\'' && s[j] == '\'')
		return (1);
	if (j - i + 1 >= 2 && s[i] == '"' && s[j] == '"')
		return (2);
	return (0);
}

char	*remove_grouping_quotes(const char *s)
{
	char	*out;
	int		i;
	int		j;
	char	quote;

	if (!s)
		return (NULL);
	out = malloc(ft_strlen(s) + 1);
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"') && quote == 0)
		{
			quote = s[i];
			i++;
			continue ;
		}
		if (quote != 0 && s[i] == quote)
		{
			quote = 0;
			i++;
			continue ;
		}
		out[j++] = s[i++];
	}
	out[j] = '\0';
	return (out);
}
