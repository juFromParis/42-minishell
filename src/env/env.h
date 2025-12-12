/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:41:00 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/12 20:40:41 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}					t_env;

int					add_env(t_env **env_list, char *variable, char *value);
int					set_env(t_env **env_list, char *variable, char *value);
int					unset_env(t_env **env_list);
t_env				*parse_env(char *envp[]);
void				free_env(t_env *env_list);
void				print_env_list(t_env *env_list);
char				*get_env_value(t_env *env_list, char *variable);
char				**to_envp(t_env *env);

#endif