/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_heredocument2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:24:23 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/15 13:24:57 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../expansion/expansion.h"
#include "../inc/minishell.h"
#include "../utils/utils.h"
#include "exec.h"
#include <sys/wait.h>

t_node	*node_hd_init(t_node *root, t_env *env)
{
	t_node	*heredoc;

	if (!root || !env)
		return (perror("Invalid arguments to node_hd_init"), NULL);
	heredoc = new_node(N_CMD, NULL, NULL);
	if (!heredoc)
		return (perror("new_node"), NULL);
	heredoc->heredoc = expand_variables(root->heredoc, env);
	if (!heredoc->heredoc)
		return (perror("expand_variables error"), NULL);
	return (heredoc);
}

t_node	*node_cmd_init(t_node *root, t_node *cmd)
{
	if (!root)
		return (perror("Invalid arguments to node_cmd_init"), NULL);
	cmd = new_node(N_CMD, NULL, NULL);
	if (!cmd)
		return (perror("new_node"), NULL);
	if (!root->cmd && root->cmd2)
		cmd->cmd = root->cmd2;
	else
		cmd->cmd = root->cmd;
	return (cmd);
}
