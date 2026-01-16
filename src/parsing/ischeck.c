/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ischeck.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:59:06 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 19:06:37 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_issign(char c)
{
	if (c == '|'
		|| c == '&'
		|| c == '('
		|| c == ')')
		return (1);
	return (0);
}

int	ft_isoperator(t_token_type type)
{
	if (type == T_PIPE || type == T_AND || type == T_OR)
		return (1);
	return (0);
}

int	ft_isredir(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_strcmp(&str[i], ">") == 0
			|| ft_strcmp(&str[i], "<") == 0
			|| ft_strcmp(&str[i], "<<") == 0
			|| ft_strcmp(&str[i], ">>") == 0)
			return (1);
		i++;
	}
	return (0);
}
