/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:49:10 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/15 17:28:52 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int	exec_command(char *pathname, char **args_null_terminated);

int	main(void)
{
	int p[2];
	pipe(p); // p[0]=read, p[1]=write

	pid_t pid1;
	pid_t pid2;
	int status1;
	int status2;

	pid1 = fork();
	if (pid1 == 0)
	{ // enfant 1 : écrit dans la pipe
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);
		exec_command("/bin/echo", (char *[]){"echo", "-n", "hello world",
			NULL});
		exit(1);
	}
	pid2 = fork();
	if (pid2 == 0)
	{ // enfant 2 : lit depuis la pipe
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		close(p[1]);
		exec_command("/usr/bin/wc", (char *[]){"wc", "-c", NULL});
		exit(1);
	}
	close(p[0]);
	close(p[1]);

	/* attendre d'abord pid2 puis pid1 */
	if (waitpid(pid2, &status2, 0) == -1)
		perror("waitpid pid2");
	if (waitpid(pid1, &status1, 0) == -1)
		perror("waitpid pid1");
	return (0);
}