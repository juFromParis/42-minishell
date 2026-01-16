/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:02:09 by vtaniga           #+#    #+#             */
/*   Updated: 2025/11/24 16:52:17 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
//node de l'ast
typedef enum 
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_OR,
	NODE_AND
} NodeType;

typedef struct s_ast_node
{
	NodeType type;
	char **args;
	t_ast_node *next;
	t_ast_node *left;
	t_ast_node *right;
} t_ast_node;

//fonction create node
t_ast_node *create_ast_node(NodeType type, char ** args)
{
	t_ast_node *new;
	new = malloc(sizeof(t_ast_node));
	if(!new)
		return(NULL);
	return(new);
}

//add node to the ast

//fonction liberation de memoire
