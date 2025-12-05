/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 10:09:21 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/04 09:41:35 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	t_token	*token;
	t_node	*ast;
	char	*input;

	token = NULL;
	ast = NULL;
	input = readline(PROMPT);
	while (input != NULL)
	{
		if (*input)
			add_history(input);
		token = lexer(input);
		print_lexer(token);
		ast = parse(token);
		print_tree(ast);
		//print_tree_debug(pipeline);
		//is_syntax_error(pipeline);
		free_ast(ast);
		input = readline(PROMPT);
	}
	return (0);
}
