/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:49:17 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/17 12:53:33 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_append(char **dst, char *line)
{
	char	*tmp;

	tmp = *dst;
	*dst = ft_strjoin(*dst, line);
	free(tmp);
	tmp = *dst;
	*dst = ft_strjoin(*dst, "\n");
	free(tmp);
}
