/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:09:58 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/15 11:20:59 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../inc/minishell.h"
#include "builtins.h"
#include <sys/wait.h>

int	builtin_echo(t_node *node)
{
	int	i;
	int	op_n;

	i = 1;
	op_n = 0;
	if (node->cmd[1] && ft_strcmp(node->cmd[1], "-n") == 0)
	{
		op_n = 1;
		i++;
	}
	while (node->cmd[i])
	{
		if ((op_n == 1 && i > 2) || (op_n == 0 && i > 1))
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(node->cmd[i], 1);
		i++;
	}
	if (op_n == 0)
		ft_putstr_fd("\n", 1);
	g_exit_status = 0;
	return (g_exit_status);
}
