/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:54:27 by vtaniga           #+#    #+#             */
/*   Updated: 2026/01/16 09:26:38 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtins.h"
#include "../env/env.h"
#include "../utils/utils.h"
#include "exec.h"
#include "sys/wait.h"

static void	handle_exec_error(char *cmd)
{
	if (write(2, cmd, ft_strlen(cmd)) == -1)
		perror("write");
	if (write(2, ": command not found\n", 20) == -1)
		perror("write");
}

int	exec_command(char *pathname, char **args_null_terminated, t_env *env)
{
	pid_t	pid;
	int		status;

	if (!pathname || !args_null_terminated || !args_null_terminated[0] || !env)
		return (perror("exec_command: Invalid arguments\n"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	else if (pid == 0)
	{
		if (execve(pathname, args_null_terminated, to_envp(env)) == -1)
		{
			handle_exec_error(args_null_terminated[0]);
			exit(127);
		}
	}
	else
	{
		if (wait(&status) == -1)
			perror("wait");
		if (WIFEXITED(status))
			return (g_exit_status = WEXITSTATUS(status), g_exit_status);
		if (WIFSIGNALED(status))
			return (g_exit_status = 128 + WTERMSIG(status), g_exit_status);
	}
	g_exit_status = 1;
	return (g_exit_status);
}

int	execute_command_node(t_node *node, t_env *env)
{
	char	*path;

	if (!node || !env)
		return (perror("execute_command_node: Invalid arguments\n"), -1);
	if ((node->cmd && is_builtin_command(node->cmd[0]))
		|| (node->cmd2 && is_builtin_command(node->cmd2[0])))
	{
		g_exit_status = execute_builtin_command(node, env);
		return (g_exit_status);
	}
	if (!node->cmd)
		return (perror("execute_command_node: cmd is NULL\n"), -1);
	path = resolve_path(node->cmd[0], env);
	if (!path)
	{
		handle_exec_error(node->cmd[0]);
		g_exit_status = 127;
		return (g_exit_status);
	}
	g_exit_status = exec_command(path, node->cmd, env);
	free(path);
	return (g_exit_status);
}
