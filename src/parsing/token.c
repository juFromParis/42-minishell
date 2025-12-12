/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:11:26 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/11 13:37:03 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = (NULL);
	return (token);
}

void	token_add_back(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!*list)
	{
		new->prev = NULL;
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	token_push(t_token **list, t_token *token, int *i)
{
	if (token != NULL)
		token_add_back(list, token);
	else
		(*i)++;
}

int	is_cmd_token(t_token_type type)
{
	return (type == T_WORD || type == T_CMD);
}
