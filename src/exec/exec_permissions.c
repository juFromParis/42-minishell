/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_permissions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 09:37:23 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/16 09:38:19 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>

#include "../builtins/builtins.h"
#include "../env/env.h"
#include "../utils/utils.h"
#include "exec.h"
#include "sys/wait.h"

int	check_redir_out_permissions(const char *file)
{
	if (!file || !*file)
		return (errno = EINVAL, -1);
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) != 0)
			return (-1);
	}
	else
	{
		if (access(".", W_OK | X_OK) != 0)
			return (-1);
	}
	return (0);
}
