/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:09:44 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:31:59 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*join;
	size_t	join_len;

	join_len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(sizeof(char) * (join_len + 1));
	if (!join)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}
/*
int	main(void)
{
	const char *s1 = "Hello, ";
	const char *s2 = "world!";
	char *join = ft_strjoin(s1, s2);

	if (join)
        	printf("%s\n", join);
	else
		printf("NULL\n");
	return 0;
}
*/
