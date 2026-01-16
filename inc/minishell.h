/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:06:35 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/16 10:03:00 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell$ "
# define SYNTAX_ERROR "syntax error near unexpected token"

# include "../libft/inc/libft.h"
# include "../get_next_line/get_next_line.h"
# include <ctype.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

extern volatile int				g_exit_status;

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
}								t_token_type;

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
}								t_node_type;

typedef struct s_token
{
	t_token_type				type;
	char						*value;
	struct s_token				*prev;
	struct s_token				*next;
}								t_token;

typedef struct s_redir
{
	char						*type;
	char						*file;
	char						*delimiter;
	char            			*content;
	struct s_redir				*next;
}								t_redir;

typedef struct s_heredoc
{
	char						*delimiter;
	char						*content;
	struct s_heredoc			*next;
}								t_heredoc;

typedef struct s_node
{
	t_node_type					type;
	char						**cmd;
	char						**cmd2;
	int 						*cmd_q;
	int 						*cmd2_q;
	char						*redir;
	char						*file;
	t_redir						*redirs;
	t_heredoc					*heredocs;
	char						*heredoc;
	struct s_node				*parent;
	struct s_node				*left;
	struct s_node				*right;
}								t_node;

typedef struct s_split
{
    char 	**args;
    int  	*quotes;
} 			t_split;

char							*get_next_line(int fd);

// LEXER & PARSING
t_token							*lexer(char *str);
t_token							*new_token(t_token_type type, char *value);
t_token							*check_operator(char *str, int *i);
t_token							*check_word(char *str, int *i);

void							token_add_back(t_token **list, t_token *new);
void							token_push(t_token **list, t_token *token,
									int *i);
void							redir_node(t_node *cmd, t_token *cur);

int								ft_issign(char c);
int								ft_isoperator(t_token_type type);
int								ft_isredir(char *str);
int								is_cmd_token(t_token_type type);


// AST
t_heredoc						*heredoc_new(char *delimiter);
t_node							*parse(t_token *cur);
t_node							*parse_logical(t_token **cur);
t_node							*parse_cmd(t_token **cur);
t_node							*parse_left(t_token **cur);
t_node							*new_node(t_node_type type, t_node *left,
									t_node *right);
t_node							*parse_left(t_token **cur);
t_node							*new_node(t_node_type type, t_node *left,
									t_node *right);
void							heredoc_add_back(t_heredoc **list,
									t_heredoc *new);
t_redir							*redir_new(char *type, char *file);
void							redir_add_back(t_redir **list, t_redir *new);
char							**split_for_redir(const char *s);
char							**split_for_arg(char const *s);
char							**add_arg(char **old_list, int size,
									char *new_arg);
char							*remove_grouping_quotes(const char *s);

int								*add_int(int *old_list, int size, int new_val);
int								quote_type(const char *s);
int								ft_arrlen_int(int *arr);

// SYNTAX ERROR
void							print_tree(t_node *root);
void							print_tree_debug(t_node *root);
void							print_lexer(t_token *token);

char							**split_redirections(const char *str);

int								is_syntax_error(t_token *node);
int								is_error_ope(t_token *node);
int								is_error_cmd(t_token *node);
int								is_error_redir(char *str);
int								is_error_sub(t_token *node);

// HEREDOC INIT
void							heredoc_child(t_heredoc *h, int fd);
void							hd_parent_signals(void);
void							hd_restore_signals(void);

int								heredoc_init(t_node *node);
int								hd_interrupted(int status);
int								hd_fork_and_wait(t_heredoc *h, int fd_read, int fd_write);

// SIGNALS
void							sig_start(int signum, void (*handler)(int));
void							sig_start_heredoc(int signum,
									void (*handler)(int));
void							sigint_prompt(int sig);
void							sigint_exec(int sig);
void							sigquit_ignore(int sig);

// EXIT
void							print_exit_status(void);
void							free_lexer(t_token **token);
void							free_ast(t_node *node);
void							free_array(char **arr);
void							free_heredocs(t_heredoc *node);

int								return_error(char *str, char **array);

#endif