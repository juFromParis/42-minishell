/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:26:48 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:53:22 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_node	*parse_sub(t_token **cur)
{
	t_node	*sub;
	t_node	*node;

	sub = parse_logical(cur);
	if (*cur && (*cur)->type == T_PARENT_CLOSE)
		*cur = (*cur)->next;
	else
		return (NULL);
	node = new_node(N_SUB, sub, NULL);
	return (node);
}

t_node	*parse_parent(t_token **cur)
{
	t_node	*node;
	t_node	*cmd;

	if (!*cur)
		return (NULL);
	if ((*cur)->type == T_PARENT_OPEN)
	{
		*cur = (*cur)->next;
		node = parse_sub(cur);
		return (node);
	}
	cmd = parse_cmd(cur);
	return (cmd);
}

t_node	*parse_pipe(t_token **cur)
{
	t_node	*left;
	t_node	*right;

	left = parse_parent(cur);
	while (*cur && (*cur)->type == T_PIPE)
	{
		*cur = (*cur)->next;
		right = parse_parent(cur);
		left = new_node(N_PIPE, left, right);
	}
	return (left);
}

t_node	*parse_logical(t_token **cur)
{
	t_node		*left;
	t_node		*right;
	t_node_type	type;

	left = parse_pipe(cur);
	while (*cur && ((*cur)->type == T_AND || (*cur)->type == T_OR))
	{
		if ((*cur)->type == T_AND)
			type = N_AND;
		else
			type = N_OR;
		*cur = (*cur)->next;
		right = parse_pipe(cur);
		left = new_node(type, left, right);
	}
	return (left);
}

t_node	*parse(t_token *cur)
{
	t_node	*ast;

	if (!cur)
		return (NULL);
	ast = parse_logical(&cur);
	return (ast);
}
