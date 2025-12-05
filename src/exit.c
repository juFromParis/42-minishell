/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:18:01 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/04 10:06:26 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_lexer(t_token **list)
{
	t_token	*tmp;
	t_token	*current;

	current = *list;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
	*list = NULL;
}


void	free_ast(t_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->cmd)
		free(node->cmd);
	free(node);
}
