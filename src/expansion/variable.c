/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:56:10 by vtaniga           #+#    #+#             */
/*   Updated: 2026/01/15 09:43:29 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../env/env.h"
#include "../utils/utils.h"
#include "expansion.h"

char	*get_variable_name(const char *str, int *len)
{
	int		i;
	char	*var_name;

	i = 0;
	if (!str || !str[0])
	{
		*len = 0;
		return (NULL);
	}
	if (str[i] == '?')
	{
		*len = 1;
		return (ft_strdup("?"));
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_strndup(str, i);
	*len = i;
	return (var_name);
}

char	*dollar_scanner(char *str)
{
	while (*str)
	{
		if (*str == '$')
			return (str);
		str++;
	}
	return (NULL);
}

// t_env	*env_new(char *name, char *value)
// {
// 	t_env	*new;

// 	new = (t_env *)malloc(sizeof(t_env));
// 	if (!new)
// 		return (NULL);
// 	new->variable = ft_strdup(name);
// 	if (!new->variable)
// 	{
// 		free(new);
// 		return (NULL);
// 	}
// 	new->value = ft_strdup(value);
// 	if (!new->value)
// 	{
// 		free(new->variable);
// 		free(new->value);
// 		free(new);
// 		return (NULL);
// 	}
// 	new->next = NULL;
// 	return (new);
// }

char	*safe_str_replace(char *original, char *dollar_pos, char *var_name,
		char *env_value)
{
	size_t	prefix_len;
	size_t	suffix_len;
	size_t	new_str_len;
	char	*new_str;
	size_t	var_len;

	prefix_len = dollar_pos - original;
	var_len = ft_strlen(var_name);
	suffix_len = ft_strlen(dollar_pos + 1 + var_len);
	new_str_len = prefix_len + ft_strlen(env_value) + suffix_len + 1;
	new_str = (char *)malloc(new_str_len);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, original, prefix_len + 1);
	ft_strlcpy(new_str + prefix_len, env_value, ft_strlen(env_value) + 1);
	ft_strlcpy(new_str + prefix_len + ft_strlen(env_value), dollar_pos + 1
		+ var_len, suffix_len + 1);
	return (new_str);
}

char	*replace_variable(char *str, t_env *env)
{
	char	*dollar_pos;
	char	*var_name;
	char	*env_value;
	char	*new_str;
	int		var_len;

	dollar_pos = dollar_scanner(str);
	if (!dollar_pos)
		return (NULL);
	var_name = get_variable_name(dollar_pos + 1, &var_len);
	if (!var_name)
		return (NULL);
	env_value = get_env_value(env, var_name);
	if (!env_value)
		return (NULL);
	new_str = safe_str_replace(str, dollar_pos, var_name, env_value);
	free(var_name);
	return (new_str);
}

char	*expand_variables(char *input, t_env *env_list)
{
	char	*current;
	char	*next;

	current = ft_strdup(input);
	if (!current)
		return (NULL);
	while (1)
	{
		next = replace_variable(current, env_list);
		if (!next)
			break ;
		free(current);
		current = next;
	}
	return (current);
}

// int	main(int argc, char **argv)
// {
// 	t_env	*env_list;
// 	char	*expanded;

// 	if (argc < 2 || !argv[1])
// 		return (1);

// 	// Build a small env list for testing
// 	env_list = env_new("HOME", "/home/vtaniga");
// 	if (!env_list)
// 		return (1);
// 	env_list->next = env_new("PATH", "/usr/bin:/bin");
// 	if (!env_list->next)
// 		return (1);
// 	env_list->next->next = env_new("SHELL", "/bin/bash");
// 	if (!env_list->next->next)
// 		return (1);

// 	expanded = expand_variables(argv[1], env_list);
// 	if (!expanded)
// 		return (1);

// 	printf("Original string: %s\n", argv[1]);
// 	printf("Final expanded string: %s\n", expanded);

// 	free(expanded);
// 	free(env_list->next->next->value);
// 	free(env_list->next->next->variable);
// 	free(env_list->next->next);
// 	free(env_list->next->value);
// 	free(env_list->next->variable);
// 	free(env_list->next);
// 	free(env_list->value);
// 	free(env_list->variable);
// 	free(env_list);

// 	return (0);
// }
