/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:32:27 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/15 17:21:51 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "exec.h"
#include "../utils/utils.h"

extern char	**environ;

int	exec_command(char *pathname, char **args_null_terminated)
{
	pid_t	pid;
	int		status;

	// if (!pathname || !args_null_terminated)
	// {
	// 	printf("verif = %s\n", pathname);
	// 	printf("exec_command: Invalid arguments\n");
	// 	return (-1);
	// }
	pid = fork();
	if (pid == -1)
	{
		// printf("Erreur fork : %s\n", strerror(errno));
		perror("errno");
		return (-1);
	}
	else if (pid == 0)
	{
		// Processus enfant
		if (execve(pathname, args_null_terminated, environ) == -1)
		{
			write(2, args_null_terminated[0],
				ft_strlen(args_null_terminated[0]));
			write(2, ": command not found", 19);
			write(2, "\n", 1);
			exit(127);
		}
	}
	else
	{
		// Processus parent
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (-1);
	}
	return (0);
}
