/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:47:28 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/05 12:07:35 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_node	*new_node(t_node_type type, t_node *left, t_node *right, char *value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->parent = NULL;
	node->left = left;
	node->right = right;
	node->redir = NULL;
	node->file = NULL;
	if (value)
	{
		node->cmd = ft_strdup(value);
	}
	else
	{
		node->cmd = NULL;
	}
	node->arg = NULL;
	return (node);
}

/*
void	lst_add_child(t_node *node, t_node *new)
{
	t_node	*last;

	if (!node || !new)
		return ;
	if (node->child == NULL)
	{
		new->parent = node;
		new->previous = NULL;
		node->child = new;
		return ;
	}
	last = node->child;
	while (last->sibling)
		last = last->sibling;
	new->parent = node;
	new->previous = last;
	last->sibling = new;
}


void	lst_add_sibling(t_node *node, t_node *new)
{
	t_node	*last;

	if (!node || !new)
		return ;

	last = node;
	while (last->sibling)
		last = last->sibling;
	new->parent = node;
	new->previous = last;
	last->sibling = new;
}

void	redir_node(t_node *cmd, t_token *cur)
{
	t_node	*node;
	t_node	*node_arg;

	node = new_node(cur->type, cur->value);
	lst_add_child(cmd, node);
	cur = cur->next;
	if (cur && cur->type == WORD)
	{
		node_arg = new_node(WORD, cur->value);
		lst_add_child(node, node_arg);
		cur = cur->next;
	}
	else
		return ;
}
*/