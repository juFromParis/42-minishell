/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:31:08 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:31:54 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strdup(char *src)
{
	char	*dest;
	int		len;
	int		i;

	len = ft_strlen(src);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
int main(void)
{
    char *dup = ft_strdup("hello");
    printf("%s\n", dup);
    return 0;
}
*/
