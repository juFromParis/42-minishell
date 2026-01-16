/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:43:05 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/15 11:46:05 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../exec/exec.h"
#include "../utils/utils.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int	filter_entries(char **entries, const char *rmv)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	j = 0;
	found = 0;
	while (entries[i])
	{
		if (ft_strnstr(entries[i], rmv, ft_strlen(entries[i])) == NULL)
		{
			found = 1;
			free(entries[i]);
		}
		else if (found)
			entries[j++] = entries[i];
		else
			j++;
		i++;
	}
	if (found)
		entries[j] = NULL;
	return (found);
}

int	filter_entries_end(char **entries, const char *rmv)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	j = 0;
	found = 0;
	while (entries[i])
	{
		if (ft_revstrncmp(entries[i], rmv, ft_strlen(rmv)) != 0)
		{
			found = 1;
			free(entries[i]);
		}
		else if (found)
			entries[j++] = entries[i];
		else
			j++;
		i++;
	}
	if (found)
		entries[j] = NULL;
	return (found);
}

int	filter_entries_start(char **entries, char *rmv)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	j = 0;
	found = 0;
	while (entries[i])
	{
		if (ft_strncmp(entries[i], rmv, ft_strlen(rmv)) != 0)
		{
			found = 1;
			free(entries[i]);
		}
		else if (found)
			entries[j++] = entries[i];
		else
			j++;
		i++;
	}
	if (found)
		entries[j] = NULL;
	return (found);
}

int	scan_for_wildcard(char *str)
{
	int	index;

	index = 0;
	if (!str)
		return (0);
	while (str[index])
	{
		if (str[index] == '*')
			return (index);
		index++;
	}
	return (0);
}
