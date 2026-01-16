/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_ope.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:30:37 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/10 13:54:31 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

int	is_error_ope(t_token *token)
{
	t_token	*next;

	if (!token)
		return (0);
	if (ft_isoperator(token->type) && token->prev == NULL)
		return (printf("bash: " SYNTAX_ERROR " `%s'\n", token->value), 1);
	if (ft_isoperator(token->type) && token->next == NULL)
		return (printf("bash: " SYNTAX_ERROR " `newline'\n"), 1);
	if (ft_isoperator(token->type) && ft_isoperator(token->next->type))
	{
		next = token->next;
		if ((token->type == T_OR && next->type == T_OR)
			|| (token->type == T_AND && next->type == T_AND))
			return (0);
		return (printf("bash: " SYNTAX_ERROR " `%s'\n", next->value), 1);
	}
	return (0);
}
