/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_heredocument2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:06:43 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/15 17:21:58 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expansion/expansion.h"
#include "../utils/utils.h"
#include "exec.h"
#include <unistd.h>

int	execute_heredoc_node(char *content, t_env *env_list)
{
	int pipefd[2];
	char *expanded_content;
	expanded_content = expand_variables(content, env_list);
	if (!expanded_content)
		return (perror("expand_variables"), -1);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		free(expanded_content);
		return (-1);
	}
	pid_t pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		free(expanded_content);
		return (-1);
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		printf("Heredoc expanded content:\n%s\n", expanded_content);
		if (write(pipefd[1], expanded_content, ft_strlen(expanded_content)) ==
			-1)
		{
			perror("write");
			close(pipefd[1]);
			exit(1);
		}
		free(expanded_content);
		close(pipefd[1]);
		exit(0);
	}
	close(pipefd[1]);
	free(expanded_content);
	return (pipefd[0]);
}