/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:53:42 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/12 18:47:53 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/wait.h>

int	execute_redir_out_node(t_node *node, t_env *env)
{
	int		fd;
	int		exit_code;
	pid_t	pid;
	char	*path;

	path = NULL;
	if (!node || !env)
		return (perror("Invalid arguments to execute_redir_out_node"), -1);
	fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open"), -1);
	pid = fork();
	if (pid == 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (perror("dup2"), -1);
		if (close(fd) == -1)
			return (perror("close"), -1);
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
		return (perror("close"), -1);
	if (waitpid(pid, &exit_code, 0) == -1)
		return (perror("waitpid"), -1);
	if (WIFEXITED(exit_code))
		return (WEXITSTATUS(exit_code));
	return (-1);
}
