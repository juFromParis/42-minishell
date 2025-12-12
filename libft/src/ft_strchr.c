/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:54:10 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:31:48 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strchr(char	*str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (str + i);
		i++;
	}
	if ((char)c == '\0')
		return (str + i);
	return (0);
}
/*
int	main(void)
{
	printf("%s\n", ft_strchr("hello", 'e'));
	return 0;
}
*/
