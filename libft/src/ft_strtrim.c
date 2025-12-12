/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:49:13 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:32:35 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	check_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	int		from;
	int		to;
	int		i;

	from = 0;
	while (s1[from] && check_in_set(s1[from], set) == 1)
		from++;
	to = ft_strlen(s1) - 1;
	while (to > from && check_in_set(s1[to], set) == 1)
		to--;
	dest = malloc(sizeof(char) * ((to - from) + 2));
	if (!dest)
		return (NULL);
	i = 0;
	while (from <= to)
		dest[i++] = s1[from++];
	dest[i] = '\0';
	return (dest);
}
/*
int	main(void)
{
	char *test = ft_strtrim("  Test  ", " ");
	printf("%s\n", test);
	return 0;
}
*/
