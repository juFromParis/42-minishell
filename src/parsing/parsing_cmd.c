/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:48:56 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/16 09:58:12 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_redirection(t_node *node, char **array, int *i)
{
	char	*clean;
	int		q;
	int		len;

	if (!array[*i + 1])
		return (1);

	if (node->redir)
		free(node->redir);
	node->redir = ft_strdup(array[*i]);

	q = quote_type(array[*i + 1]);
	clean = remove_grouping_quotes(array[*i + 1]);
	if (!clean)
		return (1);

	len = ft_arrlen(node->cmd2);
	node->cmd2_q = add_int(node->cmd2_q, len, q);

	redir_add_back(&node->redirs, redir_new(array[*i], clean));

	// if (!ft_strcmp(array[*i], "<<"))
	// 	heredoc_add_back(&node->heredocs, heredoc_new(clean));
	// else
	// 	redir_add_back(&node->redirs, redir_new(array[*i], clean));
	free(clean);

	*i += 2;
	return (0);
}

static void	handle_argument(t_node *node, char *word, int after_redir)
{
	int		q;
	char	*clean;

	(void)after_redir;
	if (!word)
		return ;
	q = quote_type(word);

	clean = remove_grouping_quotes(word);
	if (!clean)
		return ;

	node->cmd = add_arg(node->cmd, ft_arrlen(node->cmd), clean);
	node->cmd_q = add_int(node->cmd_q, ft_arrlen_int(node->cmd_q), q);

	free(clean);
}

static int	parse_cmd_array(t_node *node, char **array)
{
	int	i;
	int	after_redir;

	i = 0;
	after_redir = 0;
	while (array[i])
	{
		if (!strcmp(array[i], "<") || !strcmp(array[i], ">")
			|| !strcmp(array[i], ">>") || !strcmp(array[i], "<<"))
		{
			if (handle_redirection(node, array, &i))
				return (1);
			after_redir = 1;
			continue ;
		}
		handle_argument(node, array[i], after_redir);
		i++;
	}
	return (0);
}

t_node	*parse_cmd(t_token **cur)
{
	t_node	*node;
	char	**array;

	if (!*cur || !is_cmd_token((*cur)->type))
		return (NULL);
	array = split_for_redir((*cur)->value);
	if (!array)
		return (NULL);
	node = new_node(N_CMD, NULL, NULL);
	node->cmd = NULL;
	node->cmd2 = NULL;
	node->cmd_q = NULL;
	node->cmd2_q = NULL;
	node->redir = NULL;
	node->file = NULL;
	node->redirs = NULL;
	node->heredocs = NULL;
	node->heredoc = NULL;
	if (parse_cmd_array(node, array))
	{
		free_array(array);
		free_ast(node);
		return (NULL);
	}
	free_array(array);
	*cur = (*cur)->next;
	return (node);
}
