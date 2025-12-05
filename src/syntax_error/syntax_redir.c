/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:12:55 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/04 10:03:36 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "../../inc/minishell.h" 

int	is_error_redir(t_node *node)
{
	if (!node)
		return (0);
	if (node->sibling == NULL)
	{
		if (node->parent && node->parent->sibling
			&& node->parent->sibling->type == OPE)
			return (printf("bash: "SYNTAX_ERROR" `%s'\n",
					node->parent->sibling->value), 1);
		else
			return (printf("bash: "SYNTAX_ERROR" `newline'\n"), 1);
	}
	if ((ft_strcmp(node->value, "<") == 0
			&& ft_strcmp(node->sibling->value, ">") == 0))
		return (printf("bash: "SYNTAX_ERROR" `newline'\n"), 1);
	if (ft_strcmp(node->value, ">") == 0
		&& ft_strcmp(node->sibling->value, "<") == 0)
		return (printf("bash: "SYNTAX_ERROR" `<'\n"), 1);
	if (node->sibling
		&& (node->sibling->type == RDR || node->sibling->type == OPE))
		return (printf("bash: "SYNTAX_ERROR" `%s'\n", node->sibling->value), 1);
	return (0);
}
*/