/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:28:48 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/15 12:46:58 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../builtins/builtins.h"
#include "../env/env.h"
#include "../expansion/expansion.h"
#include "../parsing/parsing.h"

static char	*expand(char *arg, t_env *env_list)
{
	char	*res;
	char	*old;

	res = NULL;
	old = arg;
	if (!arg || !env_list)
		return (NULL);
	res = expand_variables(arg, env_list);
	return (res);
}

char	**expand_args(char **args, int *quotes, t_env *env)
{
	int		i;
	char	*expanded;
	char	*old;
	char *tmp;

	old = NULL;
	if (!args || !env)
		return (NULL);
	i = 1;
	while (args[i])
	{
		if( quotes[i] == 1)
		{
			i++;
			continue ;
		}
		expanded = expand(args[i], env);
		tmp = args[i];
		args[i] = expanded;
		free(tmp);
		i++;
	}
	return (args);
}

static size_t	scan_for_wildcard(char **args, int *quotes)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '*') && quotes[i] == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**expand_wildcard_in_args(char **args, int *quotes)
{
	size_t	wild_index;
	char	**tmp_expanded;
	char	**current_expanded;
	char	**current;

	current = args;
	while ((wild_index = scan_for_wildcard(current, quotes)) != (size_t)-1)
	{
		printf("found wildcard in arg[%zu]: %s\n", wild_index,
			current[wild_index]);
		tmp_expanded = expand_wildcard(current[wild_index]);
		if (!tmp_expanded)
			return (current);
		current_expanded = insert_arg(current, wild_index, tmp_expanded);
		if (!current_expanded)
		{
			free_split(tmp_expanded);
			tmp_expanded = NULL;
			return (current);
		}
		current = current_expanded;
	}
	return (current);
}

int	expand_ast(t_node *node, t_env *env)
{
	if (!node)
		return (1);
	if (node->cmd)
	{
		node->cmd = expand_args(node->cmd, node->cmd_q, env);
		node->cmd = expand_wildcard_in_args(node->cmd, node->cmd_q);
	}
	else if (node->cmd2)
	{
		node->cmd2 = expand_args(node->cmd2, node->cmd2_q, env);
		node->cmd2 = expand_wildcard_in_args(node->cmd2, node->cmd2_q);
	}
	expand_ast(node->left, env);
	expand_ast(node->right, env);
	return (0);
}
