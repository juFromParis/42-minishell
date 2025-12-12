/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_heredocument.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:48:17 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/12 22:23:01 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../expansion/expansion.h"
#include "../inc/minishell.h"
#include "../utils/utils.h"
#include "exec.h"
#include <sys/wait.h>

static int	execute_heredoc_left(t_node *node, t_env *env, int *pipefd)
{
	int		exit_code;
	pid_t	pid;

	if (!node || !node->heredoc || !env || !pipefd)
		return (perror("execute_heredocs_left: invalid arguments"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		if (close(pipefd[0]) == -1)
			perror("close");
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			perror("dup2");
		if (close(pipefd[1]) == -1)
			perror("close");
		exit_code = write(STDOUT_FILENO, node->heredoc,
				ft_strlen(node->heredoc));
		_exit(exit_code);
	}
	return (pid);
}

static int	execute_heredoc_right(t_node *node, t_env *env, int *pipefd)
{
	int		exit_code;
	pid_t	pid;

	if (!node || !env || !pipefd)
		return (perror("execute_heredoc_right: invalid arguments"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		if (close(pipefd[1]) == -1)
			perror("close");
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			perror("dup2");
		if (close(pipefd[0]) == -1)
			perror("close");
		exit_code = execute_ast(node, env);
		_exit(exit_code);
	}
	return (pid);
}

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

int	execute_heredoc_node(t_node *node, t_env *env)
{
	int		pipefd[2];
	int		exit_code;
	t_node	*cmd;
	t_node	*heredoc;

	if (!node || !env)
		return (perror("Invalid arguments to execute_heredoc_node"), -1);
	cmd = NULL;
	heredoc = NULL;
	cmd = node_cmd_init(node, cmd);
	heredoc = node_hd_init(node, env);
	if (!heredoc || !cmd)
		return (perror("Node initialization failed"), -1);
	pid_t pid1, pid2;
	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid1 = execute_heredoc_left(heredoc, env, pipefd);
	if (pid1 == -1)
		return (-1);
	pid2 = execute_heredoc_right(cmd, env, pipefd);
	if (pid2 == -1)
		return (-1);
	if (close(pipefd[0]) == -1)
		perror("close");
	if (close(pipefd[1]) == -1)
		perror("close");
	if (waitpid(pid1, NULL, 0) == -1)
		perror("waitpid");
	if (waitpid(pid2, &exit_code, 0) == -1)
		perror("waitpid");
	if (WIFEXITED(exit_code))
		return (WEXITSTATUS(exit_code));
	return (-1);
}
