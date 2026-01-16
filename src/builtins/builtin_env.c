/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:09:42 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/13 11:38:10 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../inc/minishell.h"
#include "builtins.h"
#include <sys/wait.h>	

int	builtin_env(t_env *env)
{
	// int	i;

	// i = 1;
	// while (env)
    // {
    //     printf("%s=%s\n", env->variable, env->value);
    //     env = env->next;
    // }
    print_env_list(env);
    g_exit_status = 0;
	//update_return_value_env(&env, 0);
    return (g_exit_status);
}
