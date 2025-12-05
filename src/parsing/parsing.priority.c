/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.priority.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:34:21 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/04 13:42:13 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**add_arg(char **old_list, int *size, char *new_arg)
{
	char	**new_list;
	int		i;

	if (!new_arg)
		return (old_list);

	new_list = malloc(sizeof(char *) * (*size + 2));
	if (!new_list)
		return (NULL);
	i = 0;
	while (i < *size)
	{
		new_list[i] = old_list[i];
		i++;
	}
	new_list[i] = ft_strdup(new_arg);
	new_list[i + 1] = NULL;
	if (*size > 0)
		free(old_list);
	(*size)++;
	return (new_list);
}

static int	is_cmd_token(t_token_type type)
{
	if (type == T_WORD)
		return (1);
	return (0);
}

t_node	*parse_cmd(t_token **cur)
{
	t_node	*node;
	int		arg_count;

	if (!*cur)
		return (NULL);

	if (is_cmd_token((*cur)->type))
	{
		node = new_node(N_CMD, NULL, NULL, (*cur)->value);
		if (!node)
			return (NULL);

		*cur = (*cur)->next;

		node->arg = NULL;
		arg_count = 0;
		while (*cur)
		{
			if ((*cur)->type == T_WORD)
			{
				//printf("Add arg : %s\n", (*cur)->value);
				node->arg = add_arg(node->arg, &arg_count, (*cur)->value);
				*cur = (*cur)->next;
			}
			else
				break ;
		}
		return (node);
	}
	return (NULL);
}


t_node	*parse_or(t_token **cur)
{
	t_node	*node;
	t_node	*left;
	t_node	*right;

	node = NULL;
	left = NULL;
	right = NULL;

	if (!cur || !(*cur))
		return (NULL);
	left = parse_and(cur);
	while ((*cur) && (*cur)->type == T_OR)
	{
		*cur = (*cur)->next;
		right = parse_and(cur);
		node = new_node(N_OR, left, right, NULL);
		left = node;
	}
	return (left);
}

t_node	*parse_and(t_token **cur)
{
	t_node	*node;
	t_node	*left;
	t_node	*right;

	node = NULL;
	left = NULL;
	right = NULL;

	if (!cur || !(*cur))
		return (NULL);
	left = parse_cmd(cur);
	while ((*cur) && (*cur)->type == T_AND)
	{
		*cur = (*cur)->next;
		right = parse_cmd(cur);
		node = new_node(N_AND, left, right, NULL);
		left = node;
	}
	return (left);
}

t_node	*parse(t_token *cur)
{
	t_node	*ast;

	if (!cur)
		return (NULL);

	ast = parse_or(&cur);

	return (ast);
}
