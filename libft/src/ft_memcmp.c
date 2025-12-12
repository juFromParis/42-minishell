/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:16:40 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:31:09 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_memcmp(void *ptr1, void *ptr2, size_t size)
{
	unsigned char	*temp1;
	unsigned char	*temp2;
	size_t			i;

	temp1 = (unsigned char *)ptr1;
	temp2 = (unsigned char *)ptr2;
	i = 0;
	while (i < size)
	{
		if (temp1[i] != temp2[i])
			return (temp1[i] - temp2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	printf("%d\n", ft_memcmp("abc", "abd", 3));
	return 0;
}
*/
