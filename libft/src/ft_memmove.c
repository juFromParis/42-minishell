/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:56:56 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:31:14 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char		*dest_t;
	const unsigned char	*src_t;

	dest_t = (unsigned char *)dest;
	src_t = (const unsigned char *)src;
	if (len == 0 || dest_t == src_t)
		return (dest);
	if (dest_t < src_t)
	{
		while (len--)
			*dest_t++ = *src_t++;
	}
	else
	{
		dest_t = dest_t + len;
		src_t = src_t + len;
		while (len--)
			*--dest_t = *--src_t;
	}
	return (dest);
}
/*
int	main(void)
{
	char buffer[10] = "abcdef";
	ft_memmove(buffer + 2, buffer, 4);
	printf("%s\n", buffer);
	return 0;
}
*/
