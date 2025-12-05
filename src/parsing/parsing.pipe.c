/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:26:48 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/05 09:25:55 by jderachi         ###   ########.fr       */
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

static	int	is_cmd_token(t_token_type type)
{
	if (type == T_WORD || type == T_CMD)
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
			if ((*cur)->type == T_CMD)
			{
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

t_node	*parse_logical(t_token **cur)
{
	t_node		*node;
	t_node		*left;
	t_node		*right;
	t_node_type	type;

	node = NULL;
	left = NULL;
	right = NULL;
	if (!cur || !(*cur))
		return (NULL);

	left = parse_cmd(cur);

	while (*cur)
	{
		if ((*cur)->type == T_OR || (*cur)->type == T_AND || (*cur)->type == T_PIPE)
		{
			if ((*cur)->type == T_OR)
				type = N_OR;
			else if ((*cur)->type == T_AND)
				type = N_AND;
			else
				type = N_PIPE;

			*cur = (*cur)->next;

			right = parse_cmd(cur);

			node = new_node(type, left, right, NULL);
			left = node;
		}
		else if ((*cur)->type == T_PARENT_OPEN)
		{
			*cur = (*cur)->next;
			right = parse_sub(cur);

			node = new_node(N_SUB, left, right, NULL);
			left = node;
		}
		else
			break ;
	}
	return (left);
}

t_node	*parse(t_token *cur)
{
	t_node	*ast;

	if (!cur)
		return (NULL);
	ast = parse_logical(&cur);
	return (ast);
}
