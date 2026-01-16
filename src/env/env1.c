/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:36:36 by vtaniga           #+#    #+#             */
/*   Updated: 2026/01/13 14:05:02 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../utils/utils.h"
#include "env.h"

t_env	*parse_env(char *envp[])
{
	int		i;
	char	*equal_sign;
	t_env	*env_list;

	env_list = NULL;
	i = 0;
	if (!envp)
		return (perror("invalid parse_env arguments"), NULL);
	// if (add_prompt_env(&env_list) == -1)
	// 	return (NULL);
	// if (update_prompt_env(&env_list) == -1)
	// 	return (NULL);
	if (add_return_value_env(&env_list) == -1)
		return (NULL);
	while (envp && envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			if (add_env(&env_list, envp[i], equal_sign + 1) == -1)
				return (*equal_sign = '=', free_env(env_list), NULL);
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

static char	*build_env_entry(t_env *entry)
{
	size_t	len;
	size_t	varlen;
	char	*str;

	if (!entry || !entry->variable || !entry->value)
		return (perror("invalid build_env_entry arguments"), NULL);
	varlen = ft_strlen(entry->variable);
	len = varlen + ft_strlen(entry->value) + 2;
	str = malloc(len);
	if (!str)
		return (perror("malloc failed"), NULL);
	ft_strcpy(str, entry->variable);
	str[varlen] = '=';
	ft_strcpy(str + varlen + 1, entry->value);
	return (str);
}

char	**to_envp(t_env *env)
{
	char	**envp_array;
	t_env	*current;
	size_t	i;

	envp_array = init_envp_array(env);
	if (!envp_array)
		return (perror("invalid init_envp_array arguments"), NULL);
	current = env;
	i = 0;
	while (current)
	{
		envp_array[i] = build_env_entry(current);
		if (!envp_array[i])
		{
			while (i > 0)
				free(envp_array[--i]);
			free(envp_array);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	return (envp_array);
}

char	*get_env_value(t_env *env_list, char *variable)
{
	t_env	*current;

	current = env_list;
	if (!env_list || !variable)
		return (perror("invalid get_env_value arguments"), NULL);
	while (current)
	{
		if (ft_strncmp(variable, current->variable,
				ft_strlen(current->variable)) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
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
