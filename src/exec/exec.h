/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:13:14 by vtaniga           #+#    #+#             */
/*   Updated: 2026/01/16 10:27:38 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "../../inc/minishell.h"
# include <errno.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_env	t_env;
typedef struct s_node	t_node;

char					*get_path(void);
int						path_check(char *pathname);
int						exec_command(char *pathname,
							char **args_null_terminated, t_env *env);
int						cd_command(char *path);
int						redir_file(char *str, const char *filename);
int						create_file_with_redir(const char *filename);
char					*pipeline2pathname(t_node *pipeline);
char					**pipeline2array(t_node *pipeline);
char					*resolve_path(char *cmd, t_env *env);
char					**build_args_array(t_node *node);
void					free_args(char **args);

void					free_splitted(char **splitted);
int						execute_ast(t_node *node, t_env *env);
int						execute_command_node(t_node *node, t_env *env);
int						execute_and_node(t_node *node, t_env *env);
int						execute_or_node(t_node *node, t_env *env);
int						execute_pipe_node(t_node *node, t_env *env);
int						execute_redir_node(t_node *node, t_env *env);
int						execute_redir_out_node(t_node *node, t_env *env);
int						execute_redir_in_node(t_node *node, t_env *env);
int						execute_append_node(t_node *node, t_env *env);
int						execute_heredoc_node(t_node *node, t_env *env);
int						check_redir_out_permissions(const char *file);
t_node					*node_hd_init(t_node *root, t_env *env);
t_node					*node_cmd_init(t_node *root, t_node *cmd);
#endif