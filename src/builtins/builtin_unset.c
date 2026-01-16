/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:19:10 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/15 09:48:02 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../inc/minishell.h"
#include "builtins.h"
#include <sys/wait.h>

int	builtin_unset(t_node *node, t_env **env)
{
	t_env	**cur;
	t_env	*tmp;

	if (!node->cmd[1])
		return (g_exit_status = 0, g_exit_status);
	cur = env;
	while (*cur)
	{
		if (ft_strcmp((*cur)->variable, node->cmd[1]) == 0)
		{
			tmp = *cur;
			*cur = (*cur)->next;
			free(tmp);
			return (g_exit_status);
		}
		cur = &((*cur)->next);
	}
	return (g_exit_status = 0, g_exit_status);
}

