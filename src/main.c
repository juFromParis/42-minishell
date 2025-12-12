/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 10:09:21 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 22:25:31 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "./env/env.h"
#include "./exec/exec.h"

int	main(int argc, char **argv, char **envp_raw)
{
	t_env	*envp;
	t_token	*token;
	t_node	*ast;
	char	*input;
	struct sigaction	ctr_c;
	struct sigaction	ctr_d;

	(void)argc;
	(void)argv;
	envp = parse_env(envp_raw);
	token = NULL;
	ast = NULL;
	input = readline(PROMPT);



	
	ctr_c.sa_handler = sigint_listener;
	sigemptyset(&ctr_c.sa_mask);
	ctr_c.sa_flags = SA_RESTART;
	sigaction(SIGINT, &ctr_c, NULL);

	ctr_d.sa_handler = sigterm_listener;
	sigemptyset(&ctr_d.sa_mask);
	ctr_d.sa_flags = SA_RESTART;
	sigaction(SIGTERM, &ctr_c, NULL);
	
	//sigaction(SIGQUIT, SIG_IGN);
	
	while (input != NULL)
	{
		if (*input)
			add_history(input);
		token = lexer(input);
		is_syntax_error(token);
		//print_lexer(token);
		ast = parse(token);
		free_lexer(&token);
		heredoc_init(ast);
		print_tree(ast);
		execute_ast(ast, envp);
		free_ast(ast);
		input = readline(PROMPT);
	}
	return (0);
}
