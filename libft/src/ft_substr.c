/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:57:09 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:32:37 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		dest = malloc(1);
		if (!dest)
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	if (len > (s_len - start))
		len = s_len - start;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}
/*
int main(void)
{
	const char *str = "Testdesubstrsurunechaine";
	unsigned int start = 30;
	size_t len = 5;

    	char *sub = ft_substr(str, start, len);

	if (sub)
		printf("Result : \"%s\"\n", sub);
	else
		printf("NULL\n");

    return 0;
}
*/
