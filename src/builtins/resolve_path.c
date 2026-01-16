/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:14:07 by vtaniga           #+#    #+#             */
/*   Updated: 2026/01/13 17:52:12 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../exec/exec.h"
#include "../inc/minishell.h"
#include "../utils/utils.h"
#include "builtins.h"
#include <sys/wait.h>

char	**parse_parent_folder(char *path)
{
	char	**result;
	int		i;

	printf("parse_parent_folder: path=%s\n", path);
	result = ft_split_path(path, '/');
	i = 0;
	if (!path)
		return (NULL);
	return (result);
}

// char	*resolve_parent_folder(void)
// {
// 	char	*parent_folder;
// 	char	*path;
// 	char	*tmp;
// 	int		size;
// 	char	**splitted_path;
// 	int		i;

// 	path = getcwd(NULL, 0);
// 	printf("here\n");
// 	splitted_path = parse_parent_folder(path);
// 	i = 0;
// 	size = 0;
// 	parent_folder = ft_strdup("");
// 	tmp = NULL;
// 	while (splitted_path[size])
// 		size++;
// 	while (size - 1)
// 	{
// 		tmp = parent_folder;
// 		parent_folder = ft_strjoin(parent_folder, splitted_path[i]);
// 		free(tmp);
// 		size--;
// 		i++;
// 	}
// 	return (free_splitted(splitted_path), parent_folder);
// }

char	*resolve_parent_folder(void)
{
	char	*parent_folder;
	char	*path;
	char	*tmp;
	int		size;

	path = getcwd(NULL, 0);
	tmp = path;
	if (ft_strchr(path, '/') == NULL)
		return (ft_strdup("/"));
	printf("resolve_parent_folder: path=%s\n", path);
	size = 0;
	while (*path)
	{
		path++;
		size++;
	}
	while (*path != '/')
	{
		path--;
		size--;
	}
	parent_folder = ft_substr(getcwd(NULL, 0), 0, size);
	free(tmp);
	return (parent_folder);
}

char	*remove_quotes(char *str)
{
	char	*result;

	int i, j;
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			result[j] = str[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*resolve_folder_path(t_node *node)
{
	char	*path;
	char	*tmp;

	path = NULL;
	if (node->cmd && node->cmd[1])
	{
		tmp = node->cmd[1];
		path = remove_quotes(node->cmd[1]);
		if (!path)
			path = tmp;
	}
	else if (node->cmd2 && node->cmd2[1])
	{
		tmp = node->cmd2[1];
		path = remove_quotes(node->cmd2[1]);
		if (!path)
			path = tmp;
	}
	if (!path)
		path = getcwd(NULL, 0);
	if (ft_strncmp(path, ".", 2) == 0)
		path = getcwd(NULL, 0);
	if (ft_strncmp(path, "..", 2) == 0)
		path = resolve_parent_folder();
	return (path);
}
