/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 12:11:20 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/12 18:37:29 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/utils.h"
#include "exec.h"
#include <sys/wait.h>

int	execute_redir_in_node(t_node *node, t_env *env)
{
	int		fd;
	int		exit_code;
	pid_t	pid;
	char	*path;
	char	**cmd;

	cmd = NULL;
	path = NULL;
	if (!node || !env)
		return (perror("Invalid arguments to execute_redir_in_node"), -1);
	if (node->file == NULL)
		return (perror("no file for redirection"), -1);
	fd = open(node->file, O_RDONLY);
	if (fd == -1)
		return (perror("open"), -1);
	if (!node->cmd && node->cmd2)
		cmd = node->cmd2;
	else
		cmd = node->cmd;
	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror("dup2"), -1);
		if (close(fd) == -1)
			return (perror("close"), -1);
		path = resolve_path(cmd[0], env);
		if (!path)
			return (perror("resolve_path"), -1);
		exit_code = exec_command(path, cmd, env);
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
