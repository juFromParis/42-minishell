/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:53:42 by vtaniga           #+#    #+#             */
/*   Updated: 2026/01/16 09:41:12 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/wait.h>

static void	handle_child_redir_out(t_node *node, t_env *env, int fd)
{
	char	*path;
	int		exit_code;

	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	if (close(fd) == -1)
	{
		perror("close");
		exit(1);
	}
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

int	execute_redir_out_node(t_node *node, t_env *env)
{
	int		fd;
	int		status;
	t_redir	*redir;
	pid_t	pid;

	if (!node || !node->redirs || !env)
		return (perror("Invalid arguments to execute_redir_out_node"), -1);
	redir = node->redirs;
	fd = -1;

	while (redir)
	{
		if (redir->type && ft_strcmp(redir->type, ">") == 0)
		{
			if (check_redir_out_permissions(redir->file) != 0)
				return (perror(redir->file), g_exit_status = 1, -1);
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (perror("open"), -1);
		}
		redir = redir->next;
	}

	pid = fork();
	if (pid == -1)
		return (close(fd), perror("fork"), -1);
	if (pid == 0)
		handle_child_redir_out(node, env, fd);
	if (close(fd) == -1)
		return (perror("close"), -1);
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid"), -1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);

}
