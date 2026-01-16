/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:26:26 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/16 10:33:39 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/utils.h"
#include "exec.h"
#include <sys/wait.h>

static int	apply_redirs(t_redir *r)
{
	int	fd;

	while (r)
	{
		if (r->type && !ft_strcmp(r->type, "<"))
		{
			if (!r->file)
				return (perror("redir < missing file"), -1);
			fd = open(r->file, O_RDONLY);
			if (fd < 0)
				return (perror(r->file), -1);
			if (dup2(fd, STDIN_FILENO) < 0)
				return (close(fd), perror("dup2"), -1);
			close(fd);
		}
		else if (r->type && !ft_strcmp(r->type, "<<"))
		{
			int	p[2];

			if (!r->content) // heredoc_init doit remplir ça
				return (perror("heredoc content NULL"), -1);
			if (pipe(p) < 0)
				return (perror("pipe"), -1);
			write(p[1], r->content, ft_strlen(r->content));
			close(p[1]);
			if (dup2(p[0], STDIN_FILENO) < 0)
				return (close(p[0]), perror("dup2"), -1);
			close(p[0]);
		}
		else if (r->type && !ft_strcmp(r->type, ">"))
		{
			if (!r->file)
				return (perror("redir > missing file"), -1);
			if (check_redir_out_permissions(r->file) != 0)
				return (perror(r->file), -1);
			fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (perror(r->file), -1);
			if (dup2(fd, STDOUT_FILENO) < 0)
				return (close(fd), perror("dup2"), -1);
			close(fd);
		}
		else if (r->type && !ft_strcmp(r->type, ">>"))
		{
			if (!r->file)
				return (perror("redir >> missing file"), -1);
			if (check_redir_out_permissions(r->file) != 0)
				return (perror(r->file), -1);
			fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (perror(r->file), -1);
			if (dup2(fd, STDOUT_FILENO) < 0)
				return (close(fd), perror("dup2"), -1);
			close(fd);
		}
		r = r->next;
	}
	return (0);
}

int	execute_redir_node(t_node *node, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**cmd;

	if (node->cmd2)
		cmd = node->cmd2;
	else
		cmd = node->cmd;
	if (!cmd || !cmd[0])
		return (perror("invalid command"), g_exit_status = 1, 1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), g_exit_status = 1, 1);
	if (pid == 0)
	{
		if (apply_redirs(node->redirs) != 0)
			exit(1);
		path = resolve_path(cmd[0], env);
		if (!path)
			exit(127);
		g_exit_status = exec_command(path, cmd, env);
		free(path);
		exit(g_exit_status);
	}
	if (waitpid(pid, &status, 0) < 0)
		return (perror("waitpid"), g_exit_status = 1, 1);
	if (WIFEXITED(status))
		return (g_exit_status = WEXITSTATUS(status), g_exit_status);
	return (g_exit_status = 1, 1);
}
