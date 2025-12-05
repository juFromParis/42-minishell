/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:26:48 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/05 12:11:18 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
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
*/

static int	is_cmd_token(t_token_type type)
{
	return (type == T_WORD || type == T_CMD);
}

char **parse_redir(char *cmd)
{
	char **array;

	if (ft_isredir(cmd))
		return (cmd_split(cmd));
	array = malloc(sizeof(char *) * 4);
	if (!array)
		return (NULL);
	array[0] = cmd;
	array[1] = NULL;
	array[2] = NULL;
	array[3] = NULL;
	return (array);
}


t_node	*parse_cmd(t_token **cur)
{
	t_node	*node;
	char	**cmd;

	// int		arg_count;
	if (!*cur || !is_cmd_token((*cur)->type))
		return (NULL);
	cmd = parse_redir((*cur)->value);
	node = new_node(N_CMD, NULL, NULL, cmd[0]);
	if (cmd[1])
		node->redir = cmd[1];
	if (cmd[2])
		node->file = cmd[2];
	free(cmd);
	*cur = (*cur)->next;
	/*
	node->arg = NULL;
	arg_count = 0;
	while (*cur && (*cur)->type == T_CMD)
	{
		node->arg = add_arg(node->arg, &arg_count, (*cur)->value);
		*cur = (*cur)->next;
	}
	*/
	return (node);
}

t_node	*parse_sub(t_token **cur)
{
	t_node	*sub;
	t_node	*node;

	sub = parse_logical(cur);
	if (*cur && (*cur)->type == T_PARENT_CLOSE)
		*cur = (*cur)->next;
	else
		return (NULL);
	node = new_node(N_SUB, sub, NULL, NULL);
	return (node);
}

t_node	*parse_parent(t_token **cur)
{
	t_node	*node;
	t_node	*cmd;

	if (!*cur)
		return (NULL);

	if ((*cur)->type == T_PARENT_OPEN)
	{
		*cur = (*cur)->next;
		node = parse_sub(cur);
		return (node);
	}
	cmd = parse_cmd(cur);
	return (cmd);
}

t_node *parse_pipe(t_token **cur)
{
	t_node	*left;
	t_node	*right;

	left = parse_parent(cur);
	while (*cur && (*cur)->type == T_PIPE)
	{
		*cur = (*cur)->next;
		right = parse_parent(cur);
		left = new_node(N_PIPE, left, right, NULL);
	}
	return (left);
}

t_node	*parse_logical(t_token **cur)
{
	t_node		*left;
	t_node		*right;
	t_node_type	type;

	left = parse_pipe(cur);
	while (*cur && ((*cur)->type == T_AND || (*cur)->type == T_OR))
	{
		if ((*cur)->type == T_AND)
			type = N_AND;
		else
			type = N_OR;
		*cur = (*cur)->next;
		right = parse_pipe(cur);
		left = new_node(type, left, right, NULL);
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
