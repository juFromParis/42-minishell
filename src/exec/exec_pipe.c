/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:48:17 by vtaniga           #+#    #+#             */
/*   Updated: 2026/01/13 10:13:04 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "exec.h"
#include <sys/wait.h>

static int	execute_pipe_left(t_node *node, t_env *env, int *pipefd)
{
	int		exit_code;
	pid_t	pid;

	if (!node || !env || !pipefd)
		return (perror("Invalid arguments to execute_pipe_left"), -1);
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
		exit_code = execute_ast(node->left, env);
		exit(exit_code);
	}
	return (pid);
}

static int	execute_pipe_right(t_node *node, t_env *env, int *pipefd)
{
	int		exit_code;
	pid_t	pid;

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
		exit_code = execute_ast(node->right, env);
		exit(exit_code);
	}
	return (pid);
}

int	execute_pipe_node(t_node *node, t_env *env)
{
	int		pipefd[2];
	int		status_right;
	pid_t	pid1;
	pid_t	pid2;

	if (!node || !env || pipe(pipefd) == -1)
		return (perror("Invalid arguments or pipe error"), -1);
	pid1 = execute_pipe_left(node, env, pipefd);
	if (pid1 == -1)
		return (-1);
	pid2 = execute_pipe_right(node, env, pipefd);
	if (pid2 == -1)
		return (-1);
	if (close(pipefd[0]) == -1)
		perror("close");
	if (close(pipefd[1]) == -1)
		perror("close");
	if (waitpid(pid1, NULL, 0) == -1)
		perror("waitpid");
	if (waitpid(pid2, &status_right, 0) == -1)
		perror("waitpid");
	if (WIFEXITED(status_right))
		return (g_exit_status = WEXITSTATUS(status_right), g_exit_status);
	if (WIFSIGNALED(status_right))
		return (g_exit_status = 128 + WTERMSIG(status_right), g_exit_status);
	return (g_exit_status = 1, g_exit_status);
}

// int	execute_pipe_node(t_node *node, t_env *env)
// {
// 	int		pipefd[2];
// 	int		exit_code;
// 	pid_t	pid1;
// 	pid_t	pid2;

// 	if (!node || !env || pipe(pipefd) == -1)
// 		return (perror("Invalid arguments or pipe error"), -1);
// 	pid1 = execute_pipe_left(node, env, pipefd);
// 	if (pid1 == -1)
// 		return (-1);
// 	pid2 = execute_pipe_right(node, env, pipefd);
// 	if (pid2 == -1)
// 		return (-1);
// 	if (close(pipefd[0]) == -1)
// 		perror("close");
// 	if (close(pipefd[1]) == -1)
// 		perror("close");
// 	if (waitpid(pid1, NULL, 0) == -1)
// 		perror("waitpid");
// 	if (waitpid(pid2, &exit_code, 0) == -1)
// 		perror("waitpid");
// 	if (WIFEXITED(exit_code))
// 		return (WEXITSTATUS(exit_code));
// 	return (-1);
// }
