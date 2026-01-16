/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:55:43 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/15 14:04:11 by vtaniga          ###   ########.fr       */
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

int	execute_and_node(t_node *node, t_env *env)
{
	int	exit_code;

	if (!node || !env)
		return (perror("Invalid arguments to execute_and_node"), -1);
	exit_code = execute_ast(node->left, env);
	if (exit_code == 0)
		exit_code = execute_ast(node->right, env);
	return (exit_code);
}

int	execute_or_node(t_node *node, t_env *env)
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
