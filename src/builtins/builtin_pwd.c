/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:04:27 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/09 16:00:33 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../inc/minishell.h"
#include "builtins.h"
#include <sys/wait.h>

int	builtin_pwd(t_env *env)
{
	char	*pwd;

	pwd = get_env_value(env, "PWD");
	if (pwd)
		ft_putendl_fd(pwd, 1);
	else
		ft_putchar_fd('\n', 1);
	g_exit_status = 0;
	return (g_exit_status);
}
