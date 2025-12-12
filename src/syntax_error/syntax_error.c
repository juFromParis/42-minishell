/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:46:29 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/11 10:58:05 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

int	is_error_type(t_token *node)
{
	(void)node;
	// if (ft_isoperator(node->type))
	// 	if (is_error_ope(node))
	// 		return (1);
	// if (node->type == T_CMD)
	// 	if (is_error_cmd(node))
	// 		return (1);
	return (0);
}

int	is_error_nosub(t_token *node)
{
	if (!node)
		return (0);
	if (node->value)
		if (is_error_type(node))
			return (1);
	if (node->next)
		if (is_error_nosub(node->next))
			return (1);
	return (0);
}

int	is_syntax_error(t_token *node)
{
	if (!node)
		return (0);
	if (node->value)
	{
		if (is_error_sub(node))
			return (1);
		if (is_error_nosub(node))
			return (1);
	}
	return (0);
}
