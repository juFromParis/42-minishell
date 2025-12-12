/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:57:41 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:31:05 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memchr(void *memoryBlock, int searchedChar, size_t size)
{
	unsigned char	*temp;
	size_t			i;

	temp = (unsigned char *)memoryBlock;
	i = 0;
	while (i < size)
	{
		if (temp[i] == (unsigned char)searchedChar)
			return (temp + i);
		i++;
	}
	return (0);
}
/*
int main(void)
{
	char str[] = "abcdefghijkl";
	printf("%s\n", (char *)ft_memchr(str, 'd', 6));
	return 0;
}
*/
