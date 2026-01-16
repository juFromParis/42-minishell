/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:10:02 by vtaniga           #+#    #+#             */
/*   Updated: 2026/01/15 10:42:24 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"
#include "builtins.h"

int	is_builtin_command(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

int	execute_builtin_command(t_node *node, t_env *env)
{
	char	*cmd;

	cmd = NULL;
	if (!node || !node->cmd || !node->cmd[0] || !env)
		return (perror("execute_builtin_command: Invalid arguments\n"), -1);
	if (node->cmd && node->cmd[0])
		cmd = node->cmd[0];
	else if (node->cmd2 && node->cmd2[0])
		cmd = node->cmd2[0];
	else
		return (perror("execute_builtin_command: No command found\n"), -1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (builtin_cd(node, env));
	if (ft_strcmp(cmd, "echo") == 0)
		return (builtin_echo(node));
	if (ft_strcmp(cmd, "env") == 0)
		return (builtin_env(env));
	if (ft_strcmp(cmd, "exit") == 0)
	{
		return (builtin_exit(node, env));
	}
	if (ft_strcmp(cmd, "export") == 0)
		return (builtin_export(node, env));
	if (ft_strcmp(cmd, "pwd") == 0)
		return (builtin_pwd(env));
	if (ft_strcmp(cmd, "unset") == 0)
		return (builtin_unset(node, &env));
	return (perror("execute_builtin_command: Unknown builtin command\n"), -1);
}
