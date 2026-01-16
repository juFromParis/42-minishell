/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:06:32 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/15 17:28:37 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int	exec_command(char *pathname, char **args_null_terminated);

int	main(void)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;
	int		return_code;

	status1 = 0;
	pid1 = fork();
	if (pid1 == 0)
	{ // enfant 1 du or
		exec_command("/bin/ls", (char *[]){"ls", "jambon", NULL});
		exit(1);
	}
	else if (pid1 < 0)
	{
		perror("fork");
		return (1);
	}
	if (waitpid(pid1, &status1, 0) == -1)
		return (perror("waitpid pid1"), 1);
	if (WIFEXITED(status1) && WEXITSTATUS(status1) == 0)
		return (WEXITSTATUS(status1));
	pid2 = fork();
	if (pid2 == 0)
	{ // enfant 2 du or
		printf("in exec wc\n");
		exec_command("/usr/bin/ls", (char *[]){"ls", "-l", NULL});
		exit(1);
	}
	else if (pid2 < 0)
	{
		perror("fork");
		return (1);
	}
	if (waitpid(pid2, &status2, 0) == -1)
	{
		printf("here1\n");
		return (perror("waitpid pid2"), 1);
	}
	printf("here2\n");
	if (WIFEXITED(status2) && WEXITSTATUS(status2) == 0)
		return (WEXITSTATUS(status2));
	return (1);
}
