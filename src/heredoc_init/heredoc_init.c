/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:18:42 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 21:32:52 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../utils/utils.h"

static void	append_line(char **dst, char *line)
{
	char	*tmp;

	tmp = *dst;
	*dst = ft_strjoin(*dst, line);
	free(tmp);
	tmp = *dst;
	*dst = ft_strjoin(*dst, "\n");
	free(tmp);
}

static void	read_one_heredoc(t_heredoc *h_node)
{
	char	*input;
	int		is_last;

	is_last = (h_node->next == NULL);
	if (is_last)
		h_node->content = ft_strdup("");
	input = readline("> ");
	while (input)
	{
		if (ft_strcmp(input, h_node->delimiter) == 0)
		{
			free(input);
			break ;
		}
		if (is_last)
			append_line(&h_node->content, input);
		free(input);
		input = readline("> ");
	}
}

int	heredoc_init(t_node *node)
{
	t_heredoc	*h_node;
	t_heredoc	*last;

	if (!node)
		return (0);
	h_node = node->heredocs;
	last = NULL;
	while (h_node)
	{
		last = h_node;
		read_one_heredoc(h_node);
		h_node = h_node->next;
	}
	if (last && last->content)
	{
		if (node->heredoc)
			free(node->heredoc);
		node->heredoc = ft_strdup(last->content);
	}
	heredoc_init(node->left);
	heredoc_init(node->right);
	return (0);
}
