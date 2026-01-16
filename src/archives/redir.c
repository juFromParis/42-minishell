/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:02:10 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/04 12:04:41 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// test d'une redirection simple vers un fichier
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "exec.h"
#include "../utils/utils.h"

int	close_helper(int fd)
{
	if (close(fd) == -1)
	{
		perror("Erreur de fermeture du fichier");
		return (1);
	}
	return (0);
}


int	redir_file(char *str, const char *filename)
{
	int		fd;
	int		ret;
	size_t	len;

	if (!str || !filename)
	{
		perror("chaine nulle ou nom de fichier nul");
		return (1);
	}
	len = ft_strlen(str);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Erreur d'ouverture du fichier");
		return (1);
	}
	if (str)
	{
		ret = write(fd, str, len);
		if ((ssize_t)ret < (ssize_t)len)
		{
			perror("Erreur d'écriture dans le fichier");
			return (close_helper(fd), 1);
		}
	}
	close_helper(fd);
	return (0);
}

int	create_file_with_redir(const char *filename)
{
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Erreur d'ouverture du fichier");
		return (1);
	}

	close_helper(fd);
	return (0);
}