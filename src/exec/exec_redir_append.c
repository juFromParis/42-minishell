/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_append.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:09:15 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/12 19:14:36 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/wait.h>

int	execute_append_node(t_node *node, t_env *env)
{
	int fd;
	int exit_code;
	pid_t pid;
	char *path;

	path = NULL;

	if (!node || !env)
		return (perror("Invalid arguments to execute_append_node"), -1);
	fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("open"), -1);
	pid = fork();
	if (pid == 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			perror("dup2");
		if (close(fd) == -1)
			perror("close");
		path = resolve_path(node->cmd[0], env);
		if (!path)
		{
			perror("resolve_path");
			_exit(127);
		}
		exit_code = exec_command(path, node->cmd, env);
		free(path);
		_exit(exit_code);
	}
	if (close(fd) == -1)
		perror("close");
	if (waitpid(pid, &exit_code, 0) == -1)
		perror("waitpid");
	if (WIFEXITED(exit_code))
		return (WEXITSTATUS(exit_code));
	return (-1);
}