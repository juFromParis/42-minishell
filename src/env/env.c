/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:36:36 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/12 21:10:08 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../utils/utils.h"
#include "env.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	add_env(t_env **env_list, char *variable, char *value)
{
	t_env	*new_node;

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
	new_node->next = *env_list;
	*env_list = new_node;
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

t_env	*parse_env(char *envp[])
{
	int		i;
	char	*equal_sign;
	t_env	*env_list;

	env_list = NULL;
	i = 0;
	if (!envp)
		return (perror("invalid parse_env arguments"), NULL);
	while (envp && envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			add_env(&env_list, envp[i], equal_sign + 1);
			*equal_sign = '=';
		}
		i++;
	}
	return (env_list);
}

char	**init_envp_array(t_env *env)
{
	t_env	*current;
	size_t	size;
	char	**envp_array;

	size = 0;
	current = env;
	if (!env)
		return (perror("invalid init_envp_array arguments"), NULL);
	while (current)
	{
		size++;
		current = current->next;
	}
	envp_array = malloc(sizeof(char *) * (size + 1));
	if (!envp_array)
		return (perror("malloc failed"), NULL);
	envp_array[size] = NULL;
	return (envp_array);
}

char	**to_envp(t_env *env)
{
	char	**envp_array;
	t_env	*current;
	size_t	i;
	size_t	len;

	envp_array = init_envp_array(env);
	if (!envp_array)
		return (perror("invalid init_envp_array arguments"), NULL);
	current = env;
	i = 0;
	while (current)
	{
		len = ft_strlen(current->variable) + ft_strlen(current->value) + 2;
		envp_array[i] = malloc(len);
		if (!envp_array[i])
		{
			while (i > 0)
				free(envp_array[--i]);
			free(envp_array);
			return (perror("malloc failed"), NULL);
		}
		ft_strcpy(envp_array[i], current->variable);
		envp_array[i][ft_strlen(current->variable)] = '=';
		ft_strcpy(envp_array[i] + ft_strlen(current->variable) + 1,
			current->value);
		current = current->next;
		i++;
	}
	return (envp_array);
}

void	free_env(t_env *env_list)
{
	t_env	*tmp;

	if (!env_list)
		return ;
	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp->variable);
		free(tmp->value);
		free(tmp);
	}
}

void	print_env_list(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	if (!env_list)
		return ;
	while (current)
	{
		printf("%s=%s\n", current->variable, current->value);
		current = current->next;
	}
}

char	*get_env_value(t_env *env_list, char *variable)
{
	t_env	*current;

	current = env_list;
	if (!env_list || !variable)
		return (perror("invalid get_env_value arguments"), NULL);
	while (current)
	{
		if (ft_strncmp(current->variable, variable, ft_strlen(variable)) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	print_env(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("i=%d %s\n", i, envp[i]);
		i++;
	}
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	t_env	*env_list;
// 	char	*envp1[] = {ft_strdup("USER=vtaniga"),
// 			ft_strdup("HOME=/home/vtaniga"),
// 			ft_strdup("PATH=/usr/bin:/bin:/usr/local/bin"), NULL};

// 	(void)argc;
// 	(void)argv;
// 	env_list = NULL;
// 	// print_env(envp);
// 	env_list = parse_env(envp1);
// 	print_env_list(env_list);
// 	print_env(to_envp(env_list));
// 	free_env(env_list);
// 	return (0);
// }
