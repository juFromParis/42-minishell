/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:34:21 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/03 10:12:19 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


static int 	has_matching_close(t_token *cur)
{
	int	depth;

	depth = 0;
	if (!cur || cur->type != PARENT_OPEN)
		return (0);
	depth = 1;
	cur = cur->next;
	while (cur)
	{
		if (cur->type == PARENT_OPEN)
		depth++;
		else if (cur->type == PARENT_CLOSE)
		{
			depth--;
			if (depth == 0)
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}

static t_node	*parse_sub(t_token **cur)
{
	t_node	*sub;
	t_node	*node;

	*cur = (*cur)->next;
	sub = new_node(SUB, "()");
	if (!sub)
		return (NULL);
	while (*cur && (*cur)->type != PARENT_CLOSE)
	{
		if ((*cur)->type == PARENT_OPEN)
		{
			if (has_matching_close(*cur))
				node = parse_sub(cur);
			else
			{
				node = new_node(PARENT_OPEN, (*cur)->value);
				*cur = (*cur)->next;
			}
			lst_add_child(sub, node);
		}
		else if ((*cur)->type == PARENT_CLOSE)
			break ;
		else if (ft_isredir((*cur)->value))
		{
			node = new_node(RDR, (*cur)->value);
			*cur = (*cur)->next;
			lst_add_child(sub, node);
		}
		else if ((*cur)->type == WORD)
		{
			node = new_node(WORD, (*cur)->value);
			*cur = (*cur)->next;
			lst_add_child(sub, node);
		}
		else if (ft_isbuiltin((*cur)->type))
		{
			node = new_node(FCT, (*cur)->value);
			*cur = (*cur)->next;
			lst_add_child(sub, node);
		}
		else if ((*cur)->type == OPE)
		{
			node = new_node(OPE, (*cur)->value);
			*cur = (*cur)->next;
			lst_add_child(sub, node);
		}
		else
			*cur = (*cur)->next;
	}
	if (*cur && (*cur)->type == PARENT_CLOSE)
		*cur = (*cur)->next;
	return (sub);
}

static t_node	*parse_parent_token(t_token **cur)
{
	t_node	*node;

	if ((*cur)->type == PARENT_OPEN)
	{
		if (has_matching_close(*cur))
			return (parse_sub(cur));
		node = new_node(PARENT_OPEN, (*cur)->value);
		*cur = (*cur)->next;
		return (node);
	}
	else if ((*cur)->type == PARENT_CLOSE)
	{
		node = new_node(PARENT_CLOSE, (*cur)->value);
		*cur = (*cur)->next;
		return (node);
	}
	return (NULL);
}

void	parse_cmd(t_node *cmd, t_token **cur)
{
	t_node	*node;
	t_node	*sub;

	while (*cur && !ft_isoperator((*cur)->type))
	{
		if ((*cur)->type == PARENT_OPEN || (*cur)->type == PARENT_CLOSE)
		{
			sub = parse_parent_token(cur);
			lst_add_child(cmd, sub);
			continue ;
		}
		else if (ft_isredir((*cur)->value))
		{
			node = new_node(RDR, (*cur)->value);
			*cur = (*cur)->next;
			lst_add_child(cmd, node);
		}
		else if ((*cur)->type == WORD)
		{
			node = new_node(WORD, (*cur)->value);
			*cur = (*cur)->next;
			lst_add_child(cmd, node);
		}
		else if (ft_isbuiltin((*cur)->type))
		{
			node = new_node(FCT, (*cur)->value);
			*cur = (*cur)->next;
			lst_add_child(cmd, node);
		}
		else
			*cur = (*cur)->next;
	}
}

t_node	*parse_left(t_token **cur)
{
	t_node	*node;

	if (!cur || !*cur)
		return (NULL);
	if (ft_isoperator((*cur)->type))
		return (NULL);
	node = new_node(CMD, NULL);
	if (!node)
		return (NULL);
	parse_cmd(node, cur);
	return (node);
}

t_node *parse(t_token *cur)
{
	t_node	*pipeline;
	t_node	*cmd;
	t_node	*operator;
	t_token	*tmp;

	if (!cur)
		return (NULL);
	tmp = cur;
	pipeline = new_node(START, NULL);
	if (!pipeline)
		return (NULL);
	while (cur && cur->type != END)
	{
		cmd = parse_left(&cur);
		if (cmd)
			lst_add_child(pipeline, cmd);
		if (cur && ft_isoperator(cur->type))
		{
			operator = new_node(OPE, cur->value);
			lst_add_child(pipeline, operator);
			cur = cur->next;
		}
	}
	free_lexer(&tmp);
	return (pipeline);
}
