/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_append.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:09:15 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/15 17:29:19 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/wait.h>

static int	setup_append_redirection(t_node *node)
{
	int	fd;

	fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	if (close(fd) == -1)
		perror("close");
	return (0);
}

static void	execute_append_child(t_node *node, t_env *env)
{
	char	*path;
	int		exit_code;

	if (setup_append_redirection(node) == -1)
		exit(1);
	path = resolve_path(node->cmd[0], env);
	if (!path)
	{
		perror("resolve_path");
		exit(127);
	}
	exit_code = exec_command(path, node->cmd, env);
	free(path);
	exit(exit_code);
}

int	execute_append_node(t_node *node, t_env *env)
{
	int		exit_code;
	pid_t	pid;

	if (!node || !env)
		return (perror("Invalid arguments to execute_append_node"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
		execute_append_child(node, env);
	if (waitpid(pid, &exit_code, 0) == -1)
		perror("waitpid");
	if (WIFEXITED(exit_code))
		return (WEXITSTATUS(exit_code));
	return (-1);
}
