/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline2pathname.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:09:14 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/04 12:04:52 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "exec.h"
#include "../utils/utils.h"

char	*get_path(void)
{
	char	*path;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	return (path);
}

int	path_check(char *pathname)
{
	return (access(pathname, X_OK) == 0);
}

static void	free_path_array(char **path_split)
{
	int	i;

	i = 0;
	while (path_split[i])
	{
		free(path_split[i]);
		i++;
	}
	free(path_split);
}

static char	*find_cmd_name(t_node *pipeline)
{
	t_node	*cur;

	if (!pipeline)
		return (NULL);
	cur = pipeline->child;
	while (cur)
	{
		if (cur->type == CMD && cur->child)
			return (cur->child->value);
		cur = cur->sibling;
	}
	return (NULL);
}

static char	*search_in_path(char *cmd_name, char **path_split)
{
	char	*tmp;
	char	*full_path;
	int		i;

	i = 0;
	while (path_split[i])
	{
		tmp = ft_strjoin(path_split[i], "/");
		if (!tmp)
			break ;
		full_path = ft_strjoin(tmp, cmd_name);
		free(tmp);
		if (!full_path)
			break ;
		if (path_check(full_path))
		{
			free_path_array(path_split);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*pipeline2pathname(t_node *pipeline)
{
	char	*path;
	char	**path_split;
	char	*cmd_name;
	char	*result;

	cmd_name = find_cmd_name(pipeline);
	if (!cmd_name)
		return (NULL);
	if (ft_strchr(cmd_name, '/'))
		return (ft_strdup(cmd_name));
	path = get_path();
	if (!path)
	{
		strerror(errno);
		return (NULL);
	}
	path_split = ft_split(path, ':');
	if (!path_split)
		return (NULL);
	result = search_in_path(cmd_name, path_split);
	if (!result)
	{
		free_path_array(path_split);
	}
	return (result);
}
