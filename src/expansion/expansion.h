/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:02:42 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/12 21:19:07 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include <stdio.h>
typedef struct s_env	t_env;
char					*get_variable_name(const char *str, int *len);
char					*replace_variable(char *str, t_env *env);
char					*dollar_scanner(char *str);
char					**wildcard_expand(char *pattern);
char					*safe_str_replace(char *original, char *dollar_pos,
							char *var_name, char *env_value);
char					*replace_variable(char *str, t_env *env);
char					*expand_variables(char *input, t_env *env_list);
#endif