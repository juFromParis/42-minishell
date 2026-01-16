/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:52:57 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/16 00:00:00 by chatgpt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#define LEXER_COLOR     "\033[35m"
#define AST_COLOR       "\033[36m"
#define RESPONSE_COLOR  "\033[33m"
#define RESET           "\033[0m"

/* ======================= REDIR DEBUG (FULL) ======================= */
/*
** Shows: type, file, delimiter, content for each redir node.
** Note: content can be huge; if you want it truncated, tell me and I add a limit.
*/

static void	print_one_redir_full(int i, t_redir *r)
{
	printf(" redir[%d]:", i);
	printf(" type=\"%s\"", r->type ? r->type : "(null)");
	printf(" file=\"%s\"", r->file ? r->file : "(null)");
	printf(" delimiter=\"%s\"", r->delimiter ? r->delimiter : "(null)");
	if (r->content)
		printf(" content=\"%s\"", r->content);
	else
		printf(" content=NULL");
}

void	print_redirs(t_redir *r)
{
	int	i;

	i = 0;
	while (r)
	{
		print_one_redir_full(i, r);
		r = r->next;
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
	if (type == N_CMD)			return ("CMD");
	if (type == N_PIPE)			return ("PIPE");
	if (type == N_AND)			return ("AND");
	if (type == N_OR)			return ("OR");
	if (type == N_SUB)			return ("SUB");
	if (type == N_REDIR_IN)		return ("REDIR_IN");
	if (type == N_REDIR_OUT)	return ("REDIR_OUT");
	if (type == N_HEREDOC)		return ("HEREDOC");
	if (type == N_APPEND)		return ("APPEND");
	return ("UNKNOWN_NODE");
}

/* ======================= QUOTES DEBUG ======================= */

static void	print_cmd_with_q(char **cmd, int *q, const char *label)
{
	int	i;

	if (!cmd)
		return;
	printf(" %s=[", label);
	i = 0;
	while (cmd[i])
	{
		printf("\"%s\"", cmd[i]);
		if (q)
			printf("{q=%d}", q[i]);
		if (cmd[i + 1])
			printf(", ");
		i++;
	}
	printf("]");
}

/* ======================= SIMPLE LINEAR PRINT ======================= */

void	print_parse(t_node *node)
{
	if (!node)
		return;
	printf("Node type: %s", node_type_name(node->type));

	print_cmd_with_q(node->cmd, node->cmd_q, "cmd/args");

	if (node->redir)
		printf(" | redir: \"%s\"", node->redir);
	if (node->file)
		printf(" | file: \"%s\"", node->file);

	if (node->redirs)
		print_redirs(node->redirs);

	print_cmd_with_q(node->cmd2, node->cmd2_q, "cmd2");

	printf("\n");

	if (node->left)
		print_parse(node->left);
	if (node->right)
		print_parse(node->right);
}

/* ======================= PRETTY ASCII TREE ======================= */

static void	print_redirs_inline_full(t_redir *r)
{
	printf(" redirs=[");
	while (r)
	{
		/*
		** Full inline view:
		** {type=..., file=..., delim=..., content=...}
		*/
		printf("{type=%s",
			r->type ? r->type : "(null)");
		printf(",file=%s",
			r->file ? r->file : "(null)");
		printf(",delim=%s",
			r->delimiter ? r->delimiter : "(null)");
		if (r->content)
			printf(",content=%s", r->content);
		else
			printf(",content=NULL");
		printf("}");

		if (r->next)
			printf(" ");
		r = r->next;
	}
	printf("]");
}

static void	print_ast_rec(t_node *node, int depth, int is_right)
{
	int	i;

	if (!node)
		return;
	for (i = 0; i < depth; i++)
		printf("    ");
	if (depth > 0)
		printf("%s── ", is_right ? "└" : "├");

	printf("[%s", node_type_name(node->type));

	if (node->cmd)
	{
		int	k;

		printf(" cmd/args=[");
		k = 0;
		while (node->cmd[k])
		{
			printf("\"%s\"", node->cmd[k]);
			if (node->cmd_q)
				printf("{q=%d}", node->cmd_q[k]);
			if (node->cmd[k + 1])
				printf(", ");
			k++;
		}
		printf("]");
	}

	if (node->cmd2)
	{
		int	k;

		printf(" cmd2=[");
		k = 0;
		while (node->cmd2[k])
		{
			printf("\"%s\"", node->cmd2[k]);
			if (node->cmd2_q)
				printf("{q=%d}", node->cmd2_q[k]);
			if (node->cmd2[k + 1])
				printf(", ");
			k++;
		}
		printf("]");
	}

	if (node->redirs)
		print_redirs_inline_full(node->redirs);

	if (node->redir)
		printf(" redir=\"%s\"", node->redir);
	if (node->file)
		printf(" file=\"%s\"", node->file);

	printf("]\n");

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

/* ======================= DETAILED BINARY VIEW ======================= */

void	print_node_debug(t_node *node, int depth)
{
	int	i;

	if (!node)
		return;
	for (i = 0; i < depth; i++)
		printf("    ");
	printf("[%s", node_type_name(node->type));

	if (node->file)
		printf(" file=\"%s\"", node->file);

	if (node->redirs)
	{
		printf(" redirs={");
		print_redirs_inline_full(node->redirs);
		printf("}");
	}

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
