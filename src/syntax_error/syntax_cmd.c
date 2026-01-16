/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:01:31 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/15 16:47:02 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_error_cmd(t_token *token)
{
	if (!token)
		return (0);
	if (is_error_redir(token->value))
		return (1);
	return (0);
}
