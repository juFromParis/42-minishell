/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 21:02:40 by vtaniga           #+#    #+#             */
/*   Updated: 2025/07/22 15:57:53 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_buffer(int fd, char **buffer, char **quinon,
	ssize_t *bytes_read)
{
	if (*quinon)
	{
		ft_strlcpy(*buffer, *quinon, BUFFER_SIZE + 1);
		free(*quinon);
		*quinon = NULL;
		*bytes_read = ft_strlen(*buffer);
	}
	else
	{
		*bytes_read = read(fd, *buffer, BUFFER_SIZE);
		if (*bytes_read > 0)
			(*buffer)[*bytes_read] = '\0';
	}
	if (*bytes_read <= 0)
		return (0);
	return (1);
}

int	append_line(char **output, char *buffer, int index)
{
	char	*slice;
	char	*tmp;

	if (index == 0 && buffer[0] == '\0')
		return (1);
	slice = malloc(index + 2);
	if (!slice)
		return (0);
	ft_strlcpy(slice, buffer, index + 2);
	if (*output)
	{
		tmp = *output;
		*output = ft_strjoin(*output, slice);
		free(tmp);
		tmp = NULL;
	}
	else
		*output = ft_strdup(slice);
	free(slice);
	slice = NULL;
	if (!*output)
		return (0);
	return (1);
}

int	get_next_line_helper(int fd, char **output, char **quinon,
	ssize_t *bytes_read)
{
	char	*buffer;
	int		index;
	int		status;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	while (1)
	{
		if (!read_buffer(fd, &buffer, quinon, bytes_read))
			break ;
		index = 0;
		while (buffer[index] && buffer[index] != '\n')
			index++;
		if (!append_line(output, buffer, index))
			break ;
		status = handle_newline(buffer, index, quinon);
		if (status != 1)
			break ;
	}
	free(buffer);
	buffer = NULL;
	if (!*output || (*output)[0] == '\0')
		return (0);
	return (1);
}

void	cleanup(char **quinon, char **output)
{
	free(*quinon);
	*quinon = NULL;
	free(*output);
	*output = NULL;
}

char	*get_next_line(int fd)
{
	static char	*quinon;
	char		*output;
	ssize_t		bytes_read;

	bytes_read = 0;
	output = NULL;
	if (fd < 0)
		return (NULL);
	if (!get_next_line_helper(fd, &output, &quinon, &bytes_read))
	{
		cleanup(&quinon, &output);
		return (NULL);
	}
	if (bytes_read < 0 || (bytes_read == 0 && (!output || output[0] == '\0')))
	{
		cleanup(&quinon, &output);
		return (NULL);
	}
	return (output);
}
