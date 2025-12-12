/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:41:27 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/12 22:07:04 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../env/env.h"
#include "../utils/utils.h"
#include "exec.h"
#include <fcntl.h>

void	free_splitted(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

static int	execute_and_node(t_node *node, t_env *env)
{
	int	exit_code;

	if (!node || !env)
		return (perror("Invalid arguments to execute_and_node"), -1);
	exit_code = execute_ast(node->left, env);
	if (exit_code == 0)
		exit_code = execute_ast(node->right, env);
	return (exit_code);
}

static int	execute_or_node(t_node *node, t_env *env)
{
	int	exit_code;

	if (!node || !env)
		return (perror("Invalid arguments to execute_or_node"), -1);
	exit_code = execute_ast(node->left, env);
	if (exit_code != 0)
		exit_code = execute_ast(node->right, env);
	return (exit_code);
}

int	path_check(char *pathname)
{
	if (!pathname)
		return (-1);
	return (access(pathname, X_OK) == 0);
}

char	*resolve_path(char *cmd, t_env *env)
{
	char	*path;
	char	**paths;
	char	*full_path;
	char	*candidate;
	int		i;

	if (!cmd || !env)
		return (NULL);
	i = 0;
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = get_env_value(env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
		{
			free_splitted(paths);
			return (NULL);
		}
		candidate = ft_strjoin(full_path, cmd);
		if (!candidate)
		{
			free(full_path);
			free_splitted(paths);
			return (NULL);
		}
		free(full_path);
		if (path_check(candidate) == 1)
			return (free_splitted(paths), candidate);
		free(candidate);
		i++;
	}
	free_splitted(paths);
	return (NULL);
}

// char	**build_args_array(t_node *node)
// {
// 	return (node->arg);
// }

int	execute_ast(t_node *node, t_env *env)
{
	char	*content;

	content = NULL;
	if (!node || !env)
		return (perror("Invalid arguments to execute_ast"), -1);
	if (node->redir && ft_strncmp(node->redir, ">", 2) == 0)
		return (execute_redir_out_node(node, env));
	if (node->redir && ft_strncmp(node->redir, "<", 2) == 0)
		return (execute_redir_in_node(node, env));
	if (node->redir && ft_strncmp(node->redir, ">>", 3) == 0)
		return (execute_append_node(node, env));
	if (node->redir && ft_strncmp(node->redir, "<<", 3) == 0)
		return (execute_heredoc_node(node, env));
	if (node->type == N_CMD)
		return (execute_command_node(node, env));
	if (node->type == N_PIPE)
		return (execute_pipe_node(node, env));
	if (node->type == N_AND)
		return (execute_and_node(node, env));
	if (node->type == N_OR)
		return (execute_or_node(node, env));
	return (0);
}
