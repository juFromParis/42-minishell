/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:50:00 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:32:11 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
char	my_function(unsigned int i, char c)
{
	if (i > 2)
		return ('X');
	return (c);
}
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	while (s[len])
		len++;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
int	main(void)
{
	char	*test;

	test = ft_strmapi("Hellooooo", my_function);
	printf("%s", test);
	return (0);
}
*/
