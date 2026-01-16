/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:56:23 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/15 10:58:07 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../utils/utils.h"
#include "env.h"

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
