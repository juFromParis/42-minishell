/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:13:14 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/12 14:18:12 by vtaniga          ###   ########.fr       */
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
int						execute_ast(t_node *node, t_env *env);
int						execute_command_node(t_node *node, t_env *env);
int						execute_pipe_node(t_node *node, t_env *env);
int						execute_redir_out_node(t_node *node, t_env *env);
int						execute_redir_in_node(t_node *node, t_env *env);
int						execute_append_node(t_node *node, t_env *env);
int						execute_heredoc_node(t_node *node, t_env *env);
#endif