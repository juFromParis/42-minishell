/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:51:30 by vtaniga           #+#    #+#             */
/*   Updated: 2026/01/13 11:39:12 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../utils/utils.h"
#include "env.h"

int	add_env(t_env **env_list, char *variable, char *value)
{
	t_env	*new_node;
	t_env	*current;

	if (!env_list || !variable || !value)
		return (-1);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (perror("malloc"), -1);
	new_node->variable = ft_strdup(variable);
	if (!new_node->variable)
	{
		free(new_node);
		return (perror("ft_strdup"), -1);
	}
	new_node->value = ft_strdup(value);
	if (!new_node->value)
	{
		free(new_node->variable);
		free(new_node);
		return (perror("ft_strdup new_node->value"), -1);
	}
	new_node->next = NULL;
	if (!*env_list)
	{
		*env_list = new_node;
		return (0);
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (0);
}

int	set_env(t_env **env_list, char *variable, char *value)
{
	t_env	*current;

	current = *env_list;
	if (!env_list || !variable || !value)
		return (perror("invalid set_env arguments"), -1);
	while (current)
	{
		if (ft_strncmp(current->variable, variable, ft_strlen(variable)) == 0)
		{
			free(current->value);
			current->value = ft_strdup((char *)value);
			if (!current->value)
				return (perror("ft_strdup of current->value"), -1);
			return (0);
		}
		current = current->next;
	}
	return (add_env(env_list, (char *)variable, (char *)value));
}

int	remove_env(t_env **env_list, char *variable)
{
	t_env	*current;
	t_env	*prev;

	current = *env_list;
	prev = NULL;
	if (!env_list || !variable)
		return (perror("invalid remove_env arguments"), -1);
	while (current)
	{
		if (ft_strncmp(current->variable, variable, ft_strlen(variable)) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free(current->variable);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (-1);
}

int	add_prompt_env(t_env **env)
{
	if (!env)
		return (perror("invalid add_prompt_env arguments"), -1);
	add_env(env, "PROMPT", PROMPT);
	return (0);
}

int	update_prompt_env(t_env **env)
{
	char	*new_prompt;
	char	*tmp;

	tmp = NULL;
	if (!env)
		return (perror("invalid update_prompt_env arguments"), -1);
	new_prompt = ft_strjoin(PROMPT, getcwd(NULL, 0));
	tmp = new_prompt;
	new_prompt = ft_strjoin(new_prompt, "$ \001\033[0m\002");
	free(tmp);
	//set_env(env, "PROMPT", new_prompt);
	free(new_prompt);
	return (0);
}

int	add_return_value_env(t_env **env)
{
	if (!env)
		return (perror("invalid add_return_value_env arguments"), -1);
	//add_env(env, "?", "0");
	return (0);
}

int	update_return_value_env(t_env **env, int return_value)
{
	char	*value_str;

	if (!env)
		return (perror("invalid update_return_value_env arguments"), -1);
	value_str = ft_itoa(return_value);
	if (!value_str)
		return (perror("ft_itoa"), -1);
	set_env(env, "?", value_str);
	free(value_str);
	return (0);
}
