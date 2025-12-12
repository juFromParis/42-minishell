/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:18:01 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 21:32:38 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

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
	if (node->cmd)
		free_array(node->cmd);
	if (node->redir)
		free(node->redir);
	if (node->file)
		free(node->file);
	if (node->heredocs)
		free_heredocs(node->heredocs);
	if (node->heredoc)
		free(node->heredoc);
	if (node->cmd2)
		free_array(node->cmd2);
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

void	free_heredocs(t_heredoc *node)
{
	t_heredoc	*tmp;

	while (node)
	{
		tmp = node->next;
		if (node->delimiter)
			free(node->delimiter);
		if (node->content)
			free(node->content);
		free(node);
		node = tmp;
	}
}
