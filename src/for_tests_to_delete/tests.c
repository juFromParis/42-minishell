/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:52:57 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 21:32:47 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#define LEXER_COLOR     "\033[35m"
#define AST_COLOR       "\033[36m"
#define RESPONSE_COLOR  "\033[33m"
#define RESET           "\033[0m"

void	print_heredocs(t_heredoc *node)
{
	int	i;

	i = 0;
	while (node)
	{
		printf(" heredoc[%d]: delimiter=\"%s\"",
			i, node->delimiter);
		if (node->content)
			printf(" content=\"%s\"", node->content);
		else
			printf(" content=NULL");
		node = node->next;
		i++;
	}
}


/* ======================= TOKEN DEBUG ======================= */

const char	*token_type_to_str(t_token_type type)
{
	if (type == T_WORD)			return ("T_WORD");
	if (type == T_CMD)			return ("T_CMD");
	if (type == T_PIPE)			return ("T_PIPE");
	if (type == T_REDIR_IN)		return ("T_REDIR_IN");
	if (type == T_REDIR_OUT)	return ("T_REDIR_OUT");
	if (type == T_HEREDOC)		return ("T_HEREDOC");
	if (type == T_APPEND)		return ("T_APPEND");
	if (type == T_PARENT_OPEN)	return ("T_PARENT_OPEN");
	if (type == T_PARENT_CLOSE)	return ("T_PARENT_CLOSE");
	if (type == T_AND)			return ("T_AND");
	if (type == T_OR)			return ("T_OR");
	if (type == T_END)			return ("T_END");
	return ("T_UNKNOWN");
}

void	print_lexer(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	printf(LEXER_COLOR
		"\n/--LEXER-------------------------------------------------------------"
		"-----------------------------/\n\n" RESET);
	while (tmp)
	{
		printf(LEXER_COLOR "[ %s : %s ]" RESET,
			token_type_to_str(tmp->type),
			tmp->value ? tmp->value : "(null)");
		tmp = tmp->next;
	}
	printf("\n");
}

/* ======================= AST DEBUG ======================= */

static const char	*node_type_name(t_node_type type)
{
	if (type == N_CMD)		return ("CMD");
	if (type == N_PIPE)		return ("PIPE");
	if (type == N_AND)		return ("AND");
	if (type == N_OR)		return ("OR");
	if (type == N_SUB)		return ("SUB");
    if (type == N_REDIR_IN)		return ("REDIR_IN");
	if (type == N_REDIR_OUT)	return ("REDIR_OUT");
	if (type == N_HEREDOC)		return ("HEREDOC");
	if (type == N_APPEND)		return ("APPEND");
	return ("UNKNOWN_NODE");
}

/* petit print simple en préfixe */

void	print_parse(t_node *node)
{
	if (!node)
		return;
	printf("Node type: %s", node_type_name(node->type));
    
	if (node->cmd)
	{
		printf(" | cmd/args: [");
		for (int i = 0; node->cmd[i]; i++)
		{
			printf("\"%s\"", node->cmd[i]);
			if (node->cmd[i + 1])
				printf(", ");
		}
		printf("]");
	}
	if (node->file)
		printf(" | file: \"%s\"", node->file);
	if (node->heredoc)
		printf(" | heredoc: \"%s\"", node->heredoc);
	if (node->heredocs)
		print_heredocs(node->heredocs);
	if (node->heredoc)
		printf(" | heredoc: \"%s\"", node->heredoc);
	// Affichage des arguments
	if (node->cmd2)
	{
		printf(" | cmd2: [");
		for (int i = 0; node->cmd2[i]; i++)
		{
			printf("\"%s\"", node->cmd2[i]);
			if (node->cmd2[i + 1])
				printf(", ");
		}
		printf("]");
	}

	printf("\n");
    
	if (node->left)
		print_parse(node->left);
	if (node->right)
		print_parse(node->right);
}

/* joli arbre binaire ASCII */

static void print_ast_rec(t_node *node, int depth, int is_right)
{
    int i;

    if (!node)
        return;
    for (i = 0; i < depth; i++)
        printf("    ");
    if (depth > 0)
        printf("%s── ", is_right ? "└" : "├");
    
    // Affichage du type du noeud
    printf("[%s", node_type_name(node->type));
    
    // Affichage de la commande
    if (node->cmd)
	{
		printf(" cmd/args=[");
		for (int i = 0; node->cmd[i]; i++)
		{
			printf("\"%s\"", node->cmd[i]);
			if (node->cmd[i + 1])
				printf(", ");
		}
		printf("]");
	}

    // Affichage des arguments
    if (node->cmd2)
	{
		printf(" cmd2=[");
		for (int i = 0; node->cmd2[i]; i++)
		{
			printf("\"%s\"", node->cmd2[i]);
			if (node->cmd2[i + 1])
				printf(", ");
		}
		printf("]");
	}


	// Affichage des arguments
    if (node->redir)
    {
        printf(" redir=");
        printf("\"%s\"", node->redir);
    }

    // Affichage du fichier (si présent)
    if (node->file)
	{
		printf(" file=\"%s\"", node->file);
	}
        
	if (node->heredocs)
		print_heredocs(node->heredocs);

	// Affichage du fichier (si présent)
    if (node->heredoc)
	{
		printf(" heredoc (last)=\"%s\"", node->heredoc);
	}

    printf("]\n");

    // Appels récursifs pour afficher les enfants gauche et droit
    if (node->left)
        print_ast_rec(node->left, depth + 1, 0);
    if (node->right)
        print_ast_rec(node->right, depth + 1, 1);
}


void	print_tree(t_node *root)
{
	if (!root)
		return;
	printf(AST_COLOR
		"\n/--AST---------------------------------------------------------------"
		"-----------------------------/\n\n" RESET);
	print_ast_rec(root, 0, 1);
	printf("\n");
}

/* debug détaillé d'un node + ses enfants binaires */

void	print_node_debug(t_node *node, int depth)
{
	int	i;

	if (!node)
		return;
	for (i = 0; i < depth; i++)
		printf("    ");
	printf("[%s", node_type_name(node->type));
    /*
	if (node->cmd)
		printf(" \"%s\"", node->cmd);
    */
	if (node->file)
		printf(" file=\"%s\"", node->file);
	printf("]  (self=%p, parent=%p)\n", (void *)node, (void *)node->parent);
	if (node->left)
		print_node_debug(node->left, depth + 1);
	if (node->right)
		print_node_debug(node->right, depth + 1);
}

void	print_tree_debug(t_node *root)
{
	printf("\n====== DEBUG AST (binary left/right view) ======\n\n");
	print_node_debug(root, 0);
	printf("===========================================\n");
}