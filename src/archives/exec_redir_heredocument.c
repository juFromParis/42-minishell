/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_heredocument.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:25:10 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/15 17:28:18 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

int	execute_heredoc_node(t_node *node, t_env *env)
{
	char	*line;
	int		fd;
	int		exit_code;
	pid_t	pid;
	char	*path;

	path = NULL;
	(void)env;
	(void)node;
	// implementer une boucle qui lit les lignes jusqu'a ce que la ligne delimiteur soit rencontrée
	// et stocke les lignes dans un fichier temporaire ou un pipe
	line = readline(">");
	if (!line)
		return (0);
	fd = open("./tmp/tmpfile", O_CREAT | O_RDONLY, 0600);
	if (fd == -1)
	{
		free(line);
		return (perror("open"), -1);
	}
	unlink("./tmp/tmpfile");
	if (node->file == NULL)
	{
		free(line);
		return (perror("no file for redirection"), -1);
	}
	if (node->cmd == NULL || node->cmd[0] == NULL)
	{
		free(line);
		return (perror("no command for redirection"), -1);
	}
	if (!node)
		return (perror("null node"), -1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		path = resolve_path(node->cmd[0], env);
		if (!path)
			return (perror("resolve_path"), -1);
		exit_code = exec_command(path, node->cmd, env);
		free(path);
		exit(exit_code);
	}
	close(fd);
	waitpid(pid, &exit_code, 0);
	if (WIFEXITED(exit_code))
		return (WEXITSTATUS(exit_code));
	return (-1);
}
