/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:06:35 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/05 11:47:16 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\001\033[1;33m\002-minishell> \001\033[0m\002"
# define SYNTAX_ERROR "syntax error near unexpected token"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	T_WORD,
	T_CMD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_HEREDOC,
	T_APPEND,
	T_PARENT_OPEN,
	T_PARENT_CLOSE,
	T_AND,
	T_OR,
	T_END
}	t_token_type;

typedef enum e_node_type
{
	N_CMD,
	N_PIPE,
	N_REDIR_IN,
	N_REDIR_OUT,
	N_HEREDOC,
	N_APPEND,
	N_AND,
	N_OR,
	N_SUB
}	t_node_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*prev;
	struct s_token		*next;
}	t_token;

typedef struct s_node
{
	t_node_type			type;
	char				*cmd;
	char				*arg;
	char				*file;
	char				*redir;
	struct s_node		*parent;
	struct s_node		*left;
	struct s_node		*right;
}	t_node;

// UTILS
int		ft_issign(char c);
int		ft_isoperator(t_token_type type);
int		ft_isspace(char c);
int		ft_isbuiltin(t_token_type type);
int		ft_isredir(char *str);
int		ft_strcmp(char *s1, char *s2);
char **cmd_split(const char *s);

char	*ft_strdup(char *src);
char	*ft_strndup(const char *s, size_t n);

// LEXER & PARSING
t_token	*lexer(char *str);
t_token	*new_token(t_token_type type, char *value);
t_token	*check_operator(char *str, int *i);
t_token	*check_word(char *str, int *i);

t_token_type	lex_builtin(char *value);

void	token_add_back(t_token **list, t_token *new);
void	token_push(t_token **list, t_token *token, int *i);
void	redir_node(t_node *cmd, t_token *cur);

// AST
t_node	*parse(t_token *cur);
t_node	*parse_logical(t_token **cur);
t_node	*parse_cmd(t_token **cur);

t_node	*parse_left(t_token **cur);
t_node	*new_node(t_node_type type, t_node *left, t_node *right, char *value);


// SYNTAX ERROR
int		is_syntax_error(t_node *list);
int		is_error_ope(t_node *node);
int		is_error_redir(t_node *node);
int		is_error_sub(t_node *node);

void	print_tree(t_node *root);
void	print_tree_debug(t_node *root);
void	print_lexer(t_token *token);

// EXIT
void	free_lexer(t_token **token);
void	free_ast(t_node *node);

#endif