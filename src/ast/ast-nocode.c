#include "../inc/minishell.h"
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

t_ast_node *build_tree_helper(t_ast_node *top, t_ast_node *next_operator);

t_ast_node *build_tree(t_ast_node *list)
{
	return(build_tree_helper(list, list->next));
}
t_ast_node *far_right(t_ast_node *sub_ast)
{
	//faire une fonction qui va chercher le next du dernier right de l'ast 
	t_ast_node *right;
	right = sub_ast;
	while(right->right)
	{
		right = right->right; /* le prochain right*/
 	}
	return(right);
}


t_ast_node *build_tree_helper(t_ast_node *top, t_ast_node *next_operator)
{
	t_ast_node *current;
	t_ast_node *operator;
	t_ast_node *right;

	//on initialise current avec le premier maillon
	current = top;

	//on verifie s'il y a un opereateur, sinon condition d'arret
	if(!next_operator)
		return(current);

	//propagation
	operator = next_operator;
	operator->left = current;
	if (/* priorite(next_operator) > priorite(operator) */)
	{
		// on met a droite de operator l'arbre du next_operator
		operator->right = /* arbre du next_operator */;
		right = build_tree(operator->next);
	}
	else
		right = operator->next;
	operator->right = right; 
	return(build_tree_helper(operator,far_right(operator->right)->next));
	
}
