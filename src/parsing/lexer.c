/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:16:51 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/05 11:10:50 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

t_token	*check_operator(char *str, int *i)
{
	/*
	if (str[*i] == '<' && str[*i + 1] == '<')
		return ((*i) = (*i) + 2, new_token(T_HEREDOC, ft_strdup("<<")));
	else if (str[*i] == '<')
		return ((*i)++, new_token(T_REDIR_IN, ft_strdup("<")));
	else if (str[*i] == '>' && str[*i + 1] == '>')
		return ((*i) = (*i) + 2, new_token(T_APPEND, ft_strdup(">>")));
	else if (str[*i] == '>')
		return ((*i)++, new_token(T_REDIR_OUT, ft_strdup(">")));
	*/
	if (str[*i] == '&' && str[*i + 1] == '&')
		return ((*i) = (*i) + 2, new_token(T_AND, ft_strdup("&&")));
	else if (str[*i] == '|' && str[*i + 1] == '|')
		return ((*i) = (*i) + 2, new_token(T_OR, ft_strdup("||")));
	else if (str[*i] == '|')
		return ((*i)++, new_token(T_PIPE, ft_strdup("|")));
	else if (str[*i] == '(')
		return ((*i)++, new_token(T_PARENT_OPEN, ft_strdup("(")));
	else if (str[*i] == ')')
		return ((*i)++, new_token(T_PARENT_CLOSE, ft_strdup(")")));
	return (NULL);
}

t_token	*check_word(char *str, int *i)
{
	int		start;
	int		len;
	char	*word_str;
	char	quote;

	start = *i;
	while (str[*i] && !ft_issign(str[*i]))
	{
		if (str[*i] == '"' || str[*i] == '\'')
		{
			quote = str[*i];
			(*i)++;
			while (str[*i] && str[*i] != quote)
				(*i)++;
			if (str[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
	len = *i - start;
	if (ft_strcmp(&str[*i-1], " ") == 0)
		len--;
	word_str = ft_strndup(str + start, len);
	return (new_token(T_CMD, word_str));
}

/*
t_token_type	lex_builtin(char *value)
{
	if (ft_strcmp(value, "echo") == 0)
		return (T_ECHO);
	else if (ft_strcmp(value, "cd") == 0)
		return (T_CD);
	else if (ft_strcmp(value, "pwd") == 0)
		return (T_PWD);
	else if (ft_strcmp(value, "export") == 0)
		return (T_EXPORT);
	else if (ft_strcmp(value, "unset") == 0)
		return (T_UNSET);
	else if (ft_strcmp(value, "env") == 0)
		return (T_ENV);
	else if (ft_strcmp(value, "exit") == 0)
		return (T_EXIT);
	else
		return (T_WORD);
}
*/

t_token	*lexer(char *str)
{
	t_token	*token_list;
	t_token	*token;
	int		i;

	token_list = NULL;
	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (ft_issign(str[i]))
		{
			token = check_operator(str, &i);
			token_push(&token_list, token, &i);
		}
		else
		{
			token = check_word(str, &i);
			token_push(&token_list, token, &i);
		}
	}
	token_add_back(&token_list, new_token(T_END, NULL));
	free(str);
	return (token_list);
}