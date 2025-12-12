/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 10:02:07 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 19:35:27 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../utils/utils.h"

char	**gen_sub_array(t_token *node, int count)
{
	char	**array;
	int		i;

	i = 0;
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	while (node)
	{
		if (node->type == T_PARENT_OPEN || node->type == T_PARENT_CLOSE)
			array[i++] = ft_strdup(node->value);
		else if (node->type == T_PIPE || node->type == T_OR
			|| node->type == T_AND)
			array[i++] = ft_strdup("o");
		else
			array[i++] = ft_strdup("c");
		node = node->next;
	}
	array[i] = NULL;
	return (array);
}

static int	check_par_tk(char **array, int i, int *open, int *expect_closing)
{
	if (strcmp(array[i], "(") == 0)
	{
		if (i > 0 && strcmp(array[i - 1], "(") == 0)
			*expect_closing = 1;
		(*open)++;
	}
	else if (strcmp(array[i], ")") == 0)
	{
		if (*open == 0)
			return (printf("bash: " SYNTAX_ERROR " `)'\n"), 1);
		(*open)--;
	}
	return (0);
}

int	is_error_between_ope(char **array)
{
	int	i;
	int	open;
	int	expect_closing;

	i = 0;
	open = 0;
	expect_closing = 0;
	if (!array)
		return (1);
	if (strcmp(array[0], ")") == 0)
		return (printf("bash: " SYNTAX_ERROR " `)'\n"), 1);
	while (array[i])
	{
		if (check_par_tk(array, i, &open, &expect_closing))
			return (1);
		i++;
	}
	if (open > 0 || expect_closing)
		return (printf("bash: " SYNTAX_ERROR " `)'\n"), 1);
	return (0);
}

int	is_error_sub(t_token *node)
{
	char	**array;
	t_token	*tmp;
	int		i;

	tmp = node;
	i = 0;
	if (!node)
		return (0);
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	array = gen_sub_array(node, i);
	if (!array)
		return (1);
	if (is_error_between_ope(array))
		return (free_array(array), 1);
	return (free_array(array), 0);
}
