/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:39:55 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/12 12:07:33 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../inc/minishell.h"
#include "builtins.h"
#include <sys/wait.h>

int	is_valid_ident(char *str)
{
	int	i;
	int	alpha_exist;

	if (!str || str == NULL)
		return (0);
	alpha_exist = 0;
	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			alpha_exist = 1;
		i++;
	}
	if (alpha_exist == 0)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}	

int	builtin_export(t_node *node, t_env *env)
{
	int		i;
	int		k;
	char	**export;
	char	*value;
	char	*tmp;

	i = 1;
	g_exit_status = 0;
	while (node->cmd[i])
	{
		export = NULL;
		value = ft_strdup("");
		if (!value)
			return (g_exit_status = 1);
		if (ft_strchr(node->cmd[i], '='))
		{
			export = ft_split(node->cmd[i], '=');
			if (!export || !export[0] || !is_valid_ident(export[0]))
			{
				ft_putendl_fd(" not a valid identifier", 2);
				free(value);
				free_array(export);
				return (g_exit_status = 1);
			}
			k = 1;
			while (export[k])
			{
				tmp = ft_strjoin(value, export[k]);
				free(value);
				value = tmp;
				if (!value)
				{
					free_array(export);
					return (g_exit_status = 1);
				}
				k++;
			}
			add_env(&env, export[0], value);
			free_array(export);
		}
		else
		{
			if (!is_valid_ident(node->cmd[i]))
			{
				ft_putendl_fd(" not a valid identifier", 2);
				free(value);
				return (g_exit_status = 1);
			}
			add_env(&env, node->cmd[i], value);
		}
		free(value);
		i++;
	}
	return (g_exit_status);
}
