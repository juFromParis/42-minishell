/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:22:20 by vtaniga           #+#    #+#             */
/*   Updated: 2026/01/15 12:14:31 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../inc/minishell.h"
#include "builtins.h"
#include <sys/wait.h>

int	builtin_cd(t_node *node, t_env *env)
{
	char	*path;

	path = NULL;
	if (node->cmd[2])
	{
		ft_putendl_fd(" too many arguments", 2);
		return (g_exit_status = 1, g_exit_status);
	}
	path = resolve_folder_path(node);
	if (!path)
		return (g_exit_status = 1, g_exit_status);
	set_env(&env, "OLDPWD", get_env_value(env, "PWD"));
	if (chdir(path) == -1)
	{
		ft_putendl_fd(" No such file or directory", 2);
		return (g_exit_status = 1, g_exit_status);
	}
	set_env(&env, "PWD", getcwd(NULL, 0));
	return (g_exit_status = 0, g_exit_status);
}
