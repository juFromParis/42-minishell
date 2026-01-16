/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:39:17 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/12 12:22:30 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../inc/minishell.h"
#include "builtins.h"
#include <sys/wait.h>

char *epur_exit(char *src)
{
	char	*epur;
	int		len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	j = 0;
	if (!src)
		return (NULL);
	while (src[i])
	{
		if (src[i] != '\'' && src[i] != '\"')
			len++;
		i++;
	}
	epur = malloc(len + 1);
	if (!epur)
		return (NULL);
	i = 0;
	while (src[i])
	{
		if (src[i] == '\'' || src[i] == '\"')
			i++;
		else
			epur[j++] = src[i++];
	}
	epur[j] = '\0';
	return (epur);
}

int	builtin_exit(t_node *node, t_env *env)
{
	int value;

	(void)env;
	// max 256
	if (ft_arrlen(node->cmd) > 2)
	{
		ft_putendl_fd(" too many arguments", 2);
		g_exit_status = 1;
		return (g_exit_status);
	}
	if (node->cmd[1])
	{
		value = atoi(epur_exit(node->cmd[1]));
		//printf("value : %i", value);
		//printf("value_str : %s - value_int : %i", node->cmd[1], value);
		if (value < 0)
			g_exit_status = 156;
		else if (value == 0)
		{
			ft_putendl_fd(" numeric argument required", 2);
			g_exit_status = 2;
			return (g_exit_status);
		}
		else if (value > 0 && value <= 256)
			g_exit_status = value;
		else if (value > 256)
			g_exit_status = value - 256;
	}
	return (g_exit_status);
}
