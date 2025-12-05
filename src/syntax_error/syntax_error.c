/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:46:29 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/04 10:02:20 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "../../inc/minishell.h" 

int	is_error_type(t_node *node)
{
	if (node->type == OPE)
		if (is_error_ope(node))
			return (1);
	if (node->type == RDR)
		if (is_error_redir(node))
			return (1);
	if (node->type == SUB)
		if (is_error_sub(node))
			return (1);
	return (0);
}

int	is_syntax_error(t_node *list)
{
	t_node	*node;

	if (!list)
		return (0);
	node = list;
	if (node->value)
		if (is_error_type(node))
			return (1);
	if (node->child)
		if (is_syntax_error(node->child))
			return (1);
	if (node->sibling)
		if (is_syntax_error(node->sibling))
			return (1);
	return (0);
}

*/