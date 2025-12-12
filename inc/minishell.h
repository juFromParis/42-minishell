/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:06:35 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 22:25:07 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\001\033[1;33m\002-minishell> \001\033[0m\002"
# define SYNTAX_ERROR "syntax error near unexpected token"

# include <ctype.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/inc/libft.h"

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
}					t_token_type;

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
}					t_node_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_heredoc
{
	char				*delimiter;
	char				*content;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_node
{
	t_node_type			type;
	char				**cmd;
	char				**cmd2;
	char				*redir;
	char				*file;
	t_heredoc			*heredocs;
	char				*heredoc;
	struct s_node		*parent;
	struct s_node		*left;
	struct s_node		*right;
}	t_node;

// LEXER & PARSING
t_token		*lexer(char *str);
t_token		*new_token(t_token_type type, char *value);
t_token		*check_operator(char *str, int *i);
t_token		*check_word(char *str, int *i);
int			ft_issign(char c);
int			ft_isoperator(t_token_type type);
int			ft_isredir(char *str);

void		token_add_back(t_token **list, t_token *new);
void		token_push(t_token **list, t_token *token, int *i);
int			is_cmd_token(t_token_type type);
void		redir_node(t_node *cmd, t_token *cur);

// AST
t_heredoc	*heredoc_new(char *delimiter);
t_node		*parse(t_token *cur);
t_node		*parse_logical(t_token **cur);
t_node		*parse_cmd(t_token **cur);
t_node		*parse_left(t_token **cur);
t_node		*new_node(t_node_type type, t_node *left, t_node *right);
void		heredoc_add_back(t_heredoc **list, t_heredoc *new);
char		**split_for_redir(const char *s);
char		**split_for_arg(char const *s);
char		**add_arg(char **old_list, int size, char *new_arg);

t_node				*parse_left(t_token **cur);
t_node				*new_node(t_node_type type, t_node *left, t_node *right);

// SYNTAX ERROR
int			is_syntax_error(t_token *node);
int			is_error_ope(t_token *node);
int			is_error_cmd(t_token *node);
int			is_error_redir(char *str);
int			is_error_sub(t_token *node);

void		print_tree(t_node *root);
void		print_tree_debug(t_node *root);
void		print_lexer(t_token *token);

// HEREDOC INIT
int			heredoc_init(t_node *node);

// SIGNALS
void		listener(int signal_usr, siginfo_t *info, void *context);
void		sigint_listener(int sig);
void		sigterm_listener(int sig);

// EXIT
void		free_lexer(t_token **token);
void		free_ast(t_node *node);
void		free_array(char **arr);
void		free_heredocs(t_heredoc *node);

#endif