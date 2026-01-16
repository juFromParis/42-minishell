/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:33:28 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:31:12 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_t;
	const unsigned char	*src_t;

	if ((dest == NULL && src == NULL) && n > 0)
		return (NULL);
	dest_t = (unsigned char *)dest;
	src_t = (const unsigned char *)src;
	while (n > 0)
	{
		*dest_t++ = *src_t++;
		n--;
	}
	return (dest);
}
/*
int	main(void)
{
	char dest[10];
	printf("%s\n", (char *)ft_memcpy(dest, "12345", 6));
	return 0;
}
*/
