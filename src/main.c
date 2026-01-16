/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 10:09:21 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/16 10:35:33 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "./env/env.h"
#include "./exec/exec.h"
#include "./expansion/expansion.h"
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

volatile int	g_exit_status = 0;

static char	*set_prompt(void)
{
	char	*new_prompt;
	char	*tmp;

	tmp = NULL;
	new_prompt = ft_strjoin(PROMPT, getcwd(NULL, 0));
	tmp = new_prompt;
	new_prompt = ft_strjoin(new_prompt, "$ \001\033[0m\002");
	free(tmp);
	return (new_prompt);
}

static void	clean_from_gnl(char *s)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	if (len > 0 && s[len - 1] == '\n')
		s[len - 1] = '\0';
}

static char	*rdline_or_gnl(void)
{
	if (isatty(STDIN_FILENO))
		return (readline(set_prompt()));
	return (get_next_line(STDIN_FILENO));
}

static char	*replace_exit_code(char *src, int pos, int *exit_code_len)
{
	char	*exit_code;
	char	*before;
	char	*after;
	char	*tmp;
	char	*dest;

	exit_code = ft_itoa(g_exit_status);
	*exit_code_len = ft_strlen(exit_code);
	before = ft_substr(src, 0, pos);
	after = ft_strdup(src + pos + 2);
	tmp = ft_strjoin(before, exit_code);
	dest = ft_strjoin(tmp, after);
	return (dest);
}


void	expand_exit_code_array(char **array, int *array_q)
{
	int	i;
	int	j;
	int	exit_code_len;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		if (array_q[i] != 1)
		{
			j = 0;
			while (array[i][j] && array[i][j + 1])
			{
				if (array[i][j] == '$' && array[i][j + 1] == '?')
				{
					exit_code_len = 0;
					array[i] = replace_exit_code(array[i], j, &exit_code_len);
					j += exit_code_len;
				}
				else
					j++;
			}
		}
		i++;
	}
}

void	expand_exit_code_str(char *str)
{
	int	i;
	int	exit_code_len;

	if (!str)
		return ;
	i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			exit_code_len = 0;
			str = replace_exit_code(str, i, &exit_code_len);
			i += exit_code_len;
			continue ;
		}
		i++;
	}
}

void expand_exit_code(t_node *node)
{
	if (!node)
		return ;
	expand_exit_code_array(node->cmd, node->cmd_q);
	expand_exit_code_array(node->cmd2, node->cmd2_q);
	expand_exit_code_str(node->file);
	expand_exit_code_str(node->heredoc);
	expand_exit_code(node->left);
	expand_exit_code(node->right);
}

static char	*start_shell(char *input, t_env *envp)
{
	t_token	*token;
	t_node	*ast;

	clean_from_gnl(input);
	if (*input == '\0')
		return (free(input), rdline_or_gnl());
	if (*input && isatty(STDIN_FILENO))
		add_history(input);
	token = lexer(input);
	ast = parse(token);
	free_lexer(&token);

	expand_exit_code(ast);
	expand_ast(ast, envp);

	if (!ast)
		return (sig_start(SIGINT, sigint_prompt), free(input), rdline_or_gnl());
	if (!heredoc_init(ast))
	{
		//print_tree(ast);
		sig_start(SIGINT, sigint_exec);
		execute_ast(ast, envp);
	}
	free_ast(ast);
	sig_start(SIGINT, sigint_prompt);
	free(input);
	return (rdline_or_gnl());
}

int	main(int argc, char **argv, char **envp_raw)
{
	t_env	*envp;
	char	*input;

	(void)argc;
	(void)argv;
	envp = parse_env(envp_raw);
	if (!envp)
		return (1);
	sig_start(SIGINT, sigint_prompt);
	sig_start(SIGQUIT, sigquit_ignore);
	input = rdline_or_gnl();
	while (input)
		input = start_shell(input, envp);
	free_env(envp);
	return (g_exit_status);
}
