/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_heredocument1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:48:17 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/15 17:29:27 by vtaniga          ###   ########.fr       */
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
		exit(exit_code);
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
		exit(exit_code);
	}
	return (pid);
}

static int	setup_heredoc_processes(t_node *heredoc, t_node *cmd, t_env *env,
		int *pipefd)
{
	pid_t	pid1;
	pid_t	pid2;
	int		exit_code;

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
	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	exit_code = setup_heredoc_processes(heredoc, cmd, env, pipefd);
	return (exit_code);
}
