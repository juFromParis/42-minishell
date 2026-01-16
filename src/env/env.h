/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:41:00 by vtaniga           #+#    #+#             */
/*   Updated: 2026/01/09 12:07:23 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}					t_env;

int					add_env(t_env **env_list, char *variable, char *value);
int					add_prompt_env(t_env **env);
int					update_prompt_env(t_env **env);
int 				add_return_value_env(t_env **env);
int					update_return_value_env(t_env **env, int return_value);
int					set_env(t_env **env_list, char *variable, char *value);
int					unset_env(t_env **env_list);
t_env				*parse_env(char *envp[]);
void				free_env(t_env *env_list);
void				print_env_list(t_env *env_list);
char				*get_env_value(t_env *env_list, char *variable);
char				**to_envp(t_env *env);
void				print_env(char *envp[]);

#endif