/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:56:31 by vtaniga           #+#    #+#             */
/*   Updated: 2026/01/05 15:02:23 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../libft/inc/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
// char	*ft_strjoin(char const *s1, char const *s2);
// size_t	ft_strlcpy( char *dest, const char *src, size_t size);
// size_t	ft_strlen(const char *str);
// char	*ft_strdup(const char *s1);
int		handle_newline(char *buffer, int index, char **quinon);
#endif