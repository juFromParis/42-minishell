/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:54:27 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/12 22:08:28 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../utils/utils.h"
#include "exec.h"
#include "sys/wait.h"

// int	ast_node_to_pathname(t_node *node)
// {
// 	if (!node || !node->cmd || !node->cmd[0])
// 		return (-1);
// 	node->cmd[0] = resolve_path(node->cmd[0], NULL);
// 	return (0);
// }

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
			if (write(2, args_null_terminated[0],
					ft_strlen(args_null_terminated[0])) == -1)
				perror("write");
			if (write(2, ": command not found", 19) == -1)
				perror("write");
			if (write(2, "\n", 1) == -1)
				perror("write");
			_exit(127);
		}
	}
	else
	{
		if (wait(&status) == -1)
			perror("wait");
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (-1);
	}
	return (0);
}

int	execute_command_node(t_node *node, t_env *env)
{
	int		exit_code;
	char	*path;

	path = NULL;
	if (!node || !node->cmd || !node->cmd[0] || !env)
		return (perror("execute_command_node: Invalid arguments\n"), -1);
	path = resolve_path(node->cmd[0], env);
	if (!path)
	{
		if (write(2, node->cmd[0], ft_strlen(node->cmd[0])) == -1)
			perror("write");
		if (write(2, ": command not found\n", 20) == -1)
			perror("write");
		return (127);
	}
	exit_code = exec_command(path, node->cmd, env);
	free(path);
	return (exit_code);
}
