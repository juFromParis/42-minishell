/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 12:11:20 by vtaniga           #+#    #+#             */
/*   Updated: 2026/01/16 09:26:33 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/utils.h"
#include "exec.h"
#include <sys/wait.h>

static int	prepare_input_fd(const t_node *node)
{
	t_redir	*redir;
	int		fd;

	if (!node || !node->redirs)
		return (perror("no file for redirection"), -1);
	redir = node->redirs;
	fd = -1;
	while (redir)
	{
		if (redir->type && ft_strcmp(redir->type, "<") == 0)
		{
			fd = open(redir->file, O_RDONLY);
			if (fd == -1)
				return (perror(redir->file), g_exit_status = 1, -1);
		}
		redir = redir->next;
	}
	if (fd == -1)
		return (perror(node->file), g_exit_status = 1, -1);
		//return (perror("no input redirection"), -1);
	return (fd);
}

// static int	prepare_input_fd(const t_node *node)
// {
// 	int	fd;

// 	if (node->file == NULL)
// 		return (perror("no file for redirection"), -1);
// 	fd = open(node->file, O_RDONLY);
// 	if (fd == -1)
// 		return (perror(node->file), g_exit_status = 1, -1);
// 	return (fd);
// }

static int	run_child_with_stdin(int fd, char **cmd, t_env *env)
{
	char	*path;

	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("dup2"), -1);
	if (close(fd) == -1)
		return (perror("close"), -1);
	path = resolve_path(cmd[0], env);
	if (!path)
		return (perror("resolve_path"), -1);
	g_exit_status = exec_command(path, cmd, env);
	free(path);
	exit(g_exit_status);
}

static int	wait_child_status(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid"), -1);
	if (WIFEXITED(status))
		return (g_exit_status = WEXITSTATUS(status), g_exit_status);
	return (-1);
}

int	execute_redir_in_node(t_node *node, t_env *env)
{
	int		fd;
	pid_t	pid;
	char	**cmd;

	if (!node || !env)
		return (perror("Invalid arguments to execute_redir_in_node"), -1);

	fd = prepare_input_fd(node);
	if (fd < 0)
		return (-1);

	if (node->cmd2)
		cmd = node->cmd2;
	else
		cmd = node->cmd;
	if (!cmd || !cmd[0])
		return (close(fd), perror("invalid command"), -1);

	pid = fork();
	if (pid < 0)
		return (close(fd), perror("fork"), -1);
	if (pid == 0)
		run_child_with_stdin(fd, cmd, env);

	if (close(fd) == -1)
		return (perror("close"), -1);
	return (wait_child_status(pid));
}


// int	execute_redir_in_node(t_node *node, t_env *env)
// {
// 	int		fd;
// 	pid_t	pid;
// 	char	**cmd;

// 	if (!node || !env)
// 		return (perror("Invalid arguments to execute_redir_in_node"), -1);
// 	fd = prepare_input_fd(node);
// 	if (fd < 0)
// 		return (-1);
// 	if (node->cmd2)
// 		cmd = node->cmd2;
// 	else
// 		cmd = node->cmd;
// 	if (!cmd || !cmd[0])
// 		return (close(fd), perror("invalid command"), -1);
// 	pid = fork();
// 	if (pid < 0)
// 		return (close(fd), perror("fork"), -1);
// 	if (pid == 0)
// 		run_child_with_stdin(fd, cmd, env);
// 	if (close(fd) == -1)
// 		return (perror("close"), -1);
// 	return (wait_child_status(pid));
// }
