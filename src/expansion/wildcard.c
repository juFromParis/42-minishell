/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:32:41 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/12 21:17:08 by vtaniga          ###   ########.fr       */
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

// pathname expansion
int	count_dir_entries(void)
{
	DIR				*d;
	struct dirent	*dir;
	int				count;

	count = 0;
	d = opendir(".");
	if (!d)
	{
		perror("opendir");
		exit(1);
	}
	errno = 0;
	while ((dir = readdir(d)) != NULL)
	{
		count++;
	}
	if (errno != 0)
	{
		perror("readdir");
		closedir(d);
		exit(1);
	}
	closedir(d);
	return (count);
}

char	**safe_malloc_entries(int count)
{
	char	**dir_entries;

	dir_entries = malloc(sizeof(char *) * (count + 1));
	if (!dir_entries)
	{
		perror("malloc");
		exit(1);
	}
	dir_entries[count] = NULL;
	return (dir_entries);
}

void	init_helper(int err, DIR *d)
{
	if (err != 0)
	{
		perror("readdir");
		closedir(d);
		exit(1);
	}
}

char	**init_entries(char **dir_entries, DIR *d, struct dirent *dir)
{
	int	index;

	index = 0;
	d = opendir(".");
	if (!d)
	{
		perror("opendir");
		exit(1);
	}
	errno = 0;
	while ((dir = readdir(d)) != NULL)
	{
		dir_entries[index] = malloc(sizeof(char) * (ft_strlen(dir->d_name)
					+ 1));
		if (!dir_entries[index])
		{
			perror("malloc");
			while (index > 0)
				free(dir_entries[index]);
			exit(1);
		}
		ft_strcpy(dir_entries[index], dir->d_name);
		index++;
	}
	return (init_helper(errno, d), closedir(d), dir_entries);
}

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

void	print(char **entries)
{
	int	i;

	i = 0;
	while (entries[i])
	{
		printf("Entry %d: %s\n", i, entries[i]);
		i++;
	}
}

char	**get_directory_entries(void)
{
	DIR				*d;
	struct dirent	*dir;
	char			**entries;
	int				count;

	d = NULL;
	dir = NULL;
	count = count_dir_entries();
	entries = safe_malloc_entries(count);
	entries = init_entries(entries, d, dir);
	return (entries);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	parse_pattern(char *pattern, int *start_flag, int *end_flag)
{
	if (!pattern)
		return (0);
	*start_flag = 0;
	*end_flag = 0;
	if (pattern[0] != '*')
		*start_flag = 1;
	if (pattern[ft_strlen(pattern) - 1] != '*')
		*end_flag = 1;
	return (1);
}

char	**apply_pattern_filters(char **entries, char **split_pattern, int start_flag, int end_flag)
{
	int	i;

	i = 0;
	while (split_pattern[i])
	{
		if (i == 0 && start_flag)
			filter_entries_start(entries, split_pattern[i]);
		else if (split_pattern[i + 1] == NULL && end_flag)
			filter_entries_end(entries, split_pattern[i]);
		else
			filter_entries(entries, split_pattern[i]);
		i++;
	}
	return (entries);
}

char	**wildcard_expand(char *pattern)
{
	char	**split_pattern;
	char	**entries;
	int		start_flag;
	int		end_flag;

	if (!pattern)
		return (NULL);
	start_flag = 0;
	end_flag = 0;
	entries = get_directory_entries();
	parse_pattern(pattern, &start_flag, &end_flag);
	split_pattern = ft_split(pattern, '*');
	if (!split_pattern)
	{
		free_split(entries);
		return (NULL);
	}
	entries = apply_pattern_filters(entries, split_pattern, start_flag, end_flag);
	free_split(split_pattern);
	return (entries);
}

// int	main(int argc, char **argv)
// {
// 	char	**entries;
// 	// char	*full_pattern;
// 	(void) argc;
// 	(void) argv;
// 	entries = wildcard_expand(argv[1]);
// 	if(!entries)
// 		return (1);
// 	print(entries);
// 	free_split(entries);
// 	return (0);
// }

// parameter expansion

// exit status expansion