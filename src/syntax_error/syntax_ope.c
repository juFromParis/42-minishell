/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_ope.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:30:37 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/04 10:02:54 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "../../inc/minishell.h" 

int	is_error_ope(t_node *node)
{
	if (!node)
		return (0);
	if ((ft_strcmp(node->value, "||") == 0 || ft_strcmp(node->value, "&&") == 0)
		&& (!node->sibling || !node->previous || node->sibling->type == END))
	{
		printf("bash: "SYNTAX_ERROR" `%s'\n", node->value);
		return (1);
	}
	if ((ft_strcmp(node->value, "|") == 0 || ft_strcmp(node->value, "&") == 0)
		&& (!node->sibling || !node->previous || node->sibling->type == END))
	{
		ft_strcmp("bash: "SYNTAX_ERROR" `%s'\n", node->value);
		return (1);
	}
	return (0);
}
*/