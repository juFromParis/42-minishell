/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listeners.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:28:36 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/13 10:49:15 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../env/env.h"

void	sig_start(int signum, void (*handler)(int))
{
	struct sigaction	sig;

	sig.sa_handler = handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;
	sigaction(signum, &sig, NULL);
}

void	sig_start_heredoc(int signum, void (*handler)(int))
{
	struct sigaction	sig;

	sig.sa_handler = handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(signum, &sig, NULL);
}

void	sigint_prompt(int sig)
{
	(void)sig;
	g_exit_status = 130;
	if (!isatty(STDIN_FILENO))
		return ;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_exec(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(1, "\n", 1);
}

void	sigquit_ignore(int sig)
{
	(void)sig;
}
