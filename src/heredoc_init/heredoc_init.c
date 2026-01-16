/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:18:42 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/16 10:12:55 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*read_all_fd(int fd)
{
	char	buf[1025];
	char	*res;
	char	*tmp;
	ssize_t	n;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	n = read(fd, buf, 1024);
	while (n > 0)
	{
		buf[n] = '\0';
		tmp = res;
		res = ft_strjoin(res, buf);
		free(tmp);
		if (!res)
			return (NULL);
		n = read(fd, buf, 1024);
	}
	return (res);
}

static void	heredoc_child_redir(t_redir *r, int fd_write)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(0);
		if (r->delimiter && !ft_strcmp(line, r->delimiter))
		{
			free(line);
			exit(0);
		}
		write(fd_write, line, ft_strlen(line));
		write(fd_write, "\n", 1);
		free(line);
	}
}

static char	*collect_one_heredoc(t_redir *r, int *interrupted)
{
	int		fd[2];
	int		status;
	pid_t	pid;
	char	*content;

	*interrupted = 0;
	content = NULL;
	if (pipe(fd) == -1)
		return (NULL);
	hd_parent_signals();
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		heredoc_child_redir(r, fd[1]);
		exit(0);
	}
	if (pid < 0)
	{
		hd_restore_signals();
		close(fd[0]);
		close(fd[1]);
		return (NULL);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	hd_restore_signals();
	if (hd_interrupted(status))
	{
		close(fd[0]);
		*interrupted = 1;
		return (NULL);
	}
	content = read_all_fd(fd[0]);
	close(fd[0]);
	return (content);
}

static int	handle_heredocs_in_redirs(t_node *node)
{
	t_redir	*r;
	int		interrupted;
	char	*content;

	if (!node || !node->redirs)
		return (0);
	r = node->redirs;
	while (r)
	{
		if (r->type && !ft_strcmp(r->type, "<<"))
		{
			free(r->content);
			r->content = NULL;
			content = collect_one_heredoc(r, &interrupted);
			if (interrupted)
				return (g_exit_status = 130, 1);
			if (!content)
				return (1);
			r->content = content;
		}
		r = r->next;
	}
	return (0);
}

int	heredoc_init(t_node *node)
{
	if (!node)
		return (0);
	if (handle_heredocs_in_redirs(node))
		return (1);
	if (heredoc_init(node->left))
		return (1);
	if (heredoc_init(node->right))
		return (1);
	return (0);
}
