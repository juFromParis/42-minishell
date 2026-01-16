/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:47:28 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/09 12:07:50 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_node	*new_node(t_node_type type, t_node *left, t_node *right)
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
	node->heredocs = NULL;
	node->heredoc = NULL;
	node->cmd = NULL;
	node->cmd2 = NULL;
	node->cmd_q = NULL;
	node->cmd2_q = NULL;
	return (node);
}
